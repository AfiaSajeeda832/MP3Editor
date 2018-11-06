
#include <bits/stdc++.h>

using namespace std;

//vector <pair <long int, long int> > frameAddress;
vector <int> frameSize;
vector <string> audioblock;



typedef struct {
  int version;
  int layer;
  int errp;
  int bitrate;
  int freq;
  int pad;
  int priv;
  int mode;
  int modex;
  int copyright;
  int original;
  int emphasis;
} mp3header;


static int parse(const unsigned char *p, mp3header *header)
{
  const int bitrates[16] =
    {0,  32000,  40000,  48000,  56000,  64000,  80000,  96000,
         112000, 128000, 160000, 192000, 224000, 256000, 320000, 0};
  const int samplerates[4] = {44100, 48000, 32000};

  header->version = (p[1] & 0x08) >> 3;
  header->layer = 4 - ((p[1] & 0x06) >> 1);
  header->errp = (p[1] & 0x01);

  header->bitrate = bitrates[(p[2] & 0xf0) >> 4];
  header->freq = samplerates[(p[2] & 0x0c) >> 2];
  header->pad = (p[2] & 0x02) >> 1;
  header->priv = (p[2] & 0x01);

  header->mode = (p[3] & 0xc0) >> 6;
  header->modex = (p[3] & 0x30) >> 4;
  header->copyright = (p[3] & 0x08) >> 3;
  header->original = (p[3] & 0x04) >> 2;
  header->emphasis = (p[3] & 0x03);

  return 0;
}

/* calculate the size of an mp3 frame from its header */
static int framesize(mp3header *header)
{
  int size;
  int scale;

  if (header->layer == 1) scale = 48;
  else scale = 144;

  size = header->bitrate * scale / header->freq;
  /* divide by an extra factor of 2 for MPEG-2? */

  if (header->pad) size += 1;

 // frameSize.push_back(size);
  return size;
}

static int dump_header(mp3header *header, FILE *out)
{
  //fprintf(out, "  version %d layer %d", header->version, header->layer);
  if (header->version == 1 && header->layer == 1)
    {
       // fprintf(out, " (MPEG-1 layer 2)");
    }
  else if (header->version == 1 && header->layer == 2){
   // fprintf(out, " (MPEG-1 layer 2)");
  }

  else if (header->version == 1 && header->layer == 3){
  //  fprintf(out, " (MPEG-1 layer 3)");
  }

 // fprintf(out, " %d kbps %d Hz", header->bitrate/1000, header->freq);
  //fprintf(out, " %d byte frame", framesize(header));
  //fprintf(out, "\n");

  return 0;
}

static int is_mpack(const unsigned char *p, const unsigned char *e) {
  /* do we have enough room to see a 4 byte header? */
  if (p > e) return 0;
  if (e - p < 4) return 0;
  /* do we have a sync pattern? */
  if (p[0] == 0x00 && p[1] == 0x00 && p[2] == 0x01 && p[3] == 0xba) {
    return 1;
  }

  return 0;
}

static int is_mpsys(const unsigned char *p, const unsigned char *e) {
  /* do we have enough room to see a 4 byte header? */
  if (p > e) return 0;
  if (e - p < 4) return 0;
  /* do we have a sync pattern? */
  if (p[0] == 0x00 && p[1] == 0x00 && p[2] == 0x01 && p[3] == 0xbb) {
    return 1;
  }

  return 0;
}

static int is_mpmap(const unsigned char *p, const unsigned char *e) {
  /* do we have enough room to see a 4 byte header? */
  if (p > e) return 0;
  if (e - p < 4) return 0;
  /* do we have a sync pattern? */
  if (p[0] == 0x00 && p[1] == 0x00 && p[2] == 0x01 && p[3] == 0xbc) {
    return 1;
  }

  return 0;
}

static int is_mp3(const unsigned char *p, const unsigned char *e) {
  /* do we have enough room to see a 4 byte header? */
  if (p > e) return 0;
  if (e - p < 4) return 0;
  /* do we have a sync pattern? */
  if (p[0] == 0xff && (p[1]&0xe0) == 0xe0) {
    /* do we have any illegal field values? */
    if (((p[1] & 0x06) >> 1) == 0) return 0; /* no layer 4 */
    if (((p[2] & 0xf0) >> 4) == 15) return 0; /* bitrate can't be 1111 */
    if (((p[2] & 0x0c) >> 2) == 3) return 0; /* samplerate can't be 11 */
    /* looks like a sync'd header */
    return 1;
  }
  return 0;
}

static int is_id3(const unsigned char *p, const unsigned char *e) {
  /* do we have enough room to see a 10 byte header? */
  if (p > e) return 0;
  if (e - p < 10) return 0;
  /* do we have a sync pattern? */
  if (p[0] == 'I' && p[1] == 'D' && p[2] == '3') {
    if (p[3] == 0xff || p[4] == 0xff) return 0; /* illegal version */
    if (p[6] & 0x80 || p[7] & 0x80 ||
        p[8] & 0x80) return 0; /* bad length encoding */
    /* looks like an id3 header */
    return 1;
  }
  return 0;
}


vector < pair <int, int> > dump(FILE *in, FILE *out, vector < pair <int, int> > frameAddress)
{
  mp3header header;
  unsigned char *buf, *p, *e, *q;
  long length, skip;
  long hbytes = 0;


  fseek(in, 0, SEEK_END);
  length = ftell(in);
  if (length <= 0) {
    fprintf(stderr, "couldn't find the end of the file\n");
    return frameAddress;
  }
  fprintf(out, "File has %ld bytes\n", length);
  fseek(in, 0, SEEK_SET);

  buf = (unsigned char*) malloc(length);
  if (!buf) {
    fprintf(stderr, "couldn't allocate buffer for file data"
    " (%ld bytes)\n", length);
    return frameAddress;
  }

  if (fread(buf, 1, length, in) < length) {
    fprintf(stderr, "couldn't read all of the file\n");
    return frameAddress;
  }

  e = buf + length - 2;
  p = buf;
  q = p;
  while (p < e) {
    if (is_id3(p, e)) {
      if (p - q) fprintf(out, "LOST SYNC\n");
      skip = 10 + (p[9] | (p[8] << 7) | (p[7] << 14) | (p[6] << 21));
      //fprintf(out, " id3 header at 0x%08lx (%ld bytes)\n",
//    (long)(p-buf), skip);
      p += skip;
      hbytes += skip;
      q = p;
    } else if (is_mp3(p, e)) {
      if (p - q) fprintf(out, "LOST SYNC\n");
      parse(p, &header);
      skip = framesize(&header);
      if (skip <= 4) {
        //fprintf(out, " can't calculate frame size\n");
        break;
      }

      //fprintf(out, " mp3 header at 0x%08lx (%ld bytes)\n",
//    (long)(p-buf), skip);
    //store frameheader address
      frameAddress.push_back({(p-buf), skip});
    //  frameSize.push_back(skip);


      dump_header(&header, out);



      p += skip;
      hbytes += 4;
      q = p;
    } else {
      if (is_mpack(p, e)) {
    //fprintf(out, "MPEG pack header\n");
      } else if (is_mpsys(p, e)) {
  //  fprintf(out, "MPEG system header\n");
      } else if (is_mpmap(p, e)) {
//    fprintf(out, "MPEG program map\n");
      }
      //fprintf(out, "%08lx %02x\n", (long)(p-buf), (int)p[0]);
      p++;
    }
  }
  cout << "Total Frames: " << frameAddress.size() << endl;
  free(buf);
  return frameAddress;
  //cout << "OK\n " << frameAddress.size() << endl;
}

void printFrameAddress(long long index, FILE *afia, FILE *sajeeda, vector <pair <int, int> > frameAddress){
 //   FILE *sajeeda;
   // sajeeda = fopen(fileName, "rb");
    fseek(sajeeda, frameAddress[index].first, SEEK_SET);

    for(int i = 0; i < frameAddress[index].second; i++){
        unsigned char ch = fgetc(sajeeda);
        fputc(ch, afia);
    }
    //fclose(sajeeda);
}

int main(int argc, char *argv[])
{
  int i;
  FILE *in, *out = stdout,*fp1;
 // char fileName1[100], fileName2[100], fileName3[100];
  //printf("Enter 1st File Name: ");

   //scanf("%s", fileName1);
        //fileName = "1.mp3";
    FILE *fp12;
   // printf("Enter 2nd file Name: ");
    //scanf("%s", fileName2);

    in = fopen(argv[3], "rb");
    if(in == NULL){
        cout << "File open unsuccessful";
        return 0;
    }

    cout << "File opened successfully\n";

    if(!strcmp(argv[1], "1")){
        fp12 = fopen(argv[2], "wb");
    }

    else{
        fp12 = fopen(argv[2], "rb+");
        fseek(fp12, 0, SEEK_END);
    }
    vector < pair <int, int> > one;
    one = dump(in, out, one);
    FILE *afia;
    //printf("Enter the file name where you want to save: ");
    //scanf("%s", fileName3);
    // = fopen(fileName3, "wb");
    long long x, y;
    for(int i = 0; i < one.size(); i++){
            printFrameAddress(i, fp12, in, one );
      }

  return 0;
}
