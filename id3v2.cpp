#include <bits/stdc++.h>
#define bug cout << "Trust\n";

using namespace std;


bool getBit(unsigned char byte, int position) // position in range 0-7
    {
        byte = byte >> position;
        return byte & 0x1;
    }

int findSize(unsigned char x,unsigned char y,unsigned char z,unsigned char a)
{
    vector <int> vec;

    for (int i=6;i>=0;i--){
       // cout<<getBit(x,i);
        bool temp=getBit(x,i);
        vec.push_back((int)temp);
    }
  //  cout<<endl;

    for (int i=6;i>=0;i--){
       // cout<<getBit(x,i);
        bool temp=getBit(y,i);
        vec.push_back((int)temp);
    }
//    cout<<endl;

    //bits of z

    for (int i=6;i>=0;i--){
       // cout<<getBit(x,i);
        bool temp=getBit(z,i);
        vec.push_back((int)temp);
    }
    //cout<<endl;

    //bits of a

    for (int i=6;i>=0;i--){
       // cout<<getBit(x,i);
        bool temp=getBit(a,i);
        vec.push_back((int)temp);
}
    //cout<<endl;

 //   for (int i=0;i<vec.size();i++)
      //  cout<<vec[i];
        //    cout<<endl;

    int pos=0;
    int value=0;
    for(int i=vec.size()-1;i>=0;i--){
        if(vec[i]){
           value += pow(2,pos);
        }
        pos++;
    }


    cout<<value<<endl;
    cout<<endl;
    return value;
}


//#define byte char
char *byte=new char[10];

int position;

int main (int argc, char *argv[])
{
   // system("COLOR F0");
    char byte[10];
    FILE *fp;
    fp=fopen(argv[1],"rb");


    fseek(fp,0,SEEK_SET);

    cout<<"Indentifier: ";
    for (int i=0;i<3;i++)
    {
        char ch=fgetc(fp);
        byte[i]=ch;
        cout<<(unsigned char)byte[i];
    }

    cout<<"\nVersion: ";

    for (int i=3;i<5;i++)
    {
        char ch=fgetc(fp);
        byte[i]=ch;

    }
    cout<<"2."<< (unsigned int)byte[3]<<endl;

    //cout<<"Flags: ";

    bool unsynch_flag,extendHead_flag,experimental_flag;
    for (int i=5;i<6;i++)
    {
        //fgetc(byte[i]);
        unsigned char b=byte[i];
      //  cout  <<getBit(b,7) << getBit(b,6) << getBit(b,5) << getBit(b,4) <<
             //   getBit(b,3) << getBit(b,2) << getBit(b,1) << getBit(b,0)<<" ";

                unsynch_flag=getBit(b,7);
                extendHead_flag=getBit(b,6);
                experimental_flag=getBit(b,5);

    }

    cout<<"\nSize: ";
    for (int i=6;i<10;i++)
    {
       char ch=fgetc(fp);
        byte[i]=ch;
       unsigned char b=byte[i];
      // cout<< getBit(b,6) << getBit(b,5) << getBit(b,4) <<
        //        getBit(b,3) << getBit(b,2) << getBit(b,1) << getBit(b,0)<<" ";

    }


    int size =findSize(byte[6],byte[7],byte[8],byte[9]);

    if (extendHead_flag==true)
    {
        cout<<"Extended Header: present"<<endl;

    }

    else
        cout<<"Extended Header: absent"<<endl;


    bool uses_synch = (byte[5] & 0x80) != 0 ? true : false;
    bool has_extended_hdr = (byte[5] & 0x40) != 0 ? true : false;

    if ( has_extended_hdr )
        {
            int headersize = getchar() << 21 | getchar()<< 14 | getchar() << 7 | getchar();
            //file.skipBytes( headersize - 4 );
            cout<<"header size: " << headersize-4<<endl;
        }


    //from uldpzsoft
    int tagsize=size,length;
     char* buffer = new char[ tagsize ];

      //file.read( buffer ); ei gular cpp alternative janina
        //file.close();
    cout << " uses sync: " << uses_synch << endl;
     if ( uses_synch )
        {
            //bug;
            int newpos = 0;
           // char* newbuffer = new char[ tagsize ];
            char newbuffer[tagsize];
            for ( int i = 0; i < tagsize; i++ )
            {
                if ( i < tagsize - 1 && (buffer[i] & 0xFF) == 0xFF && buffer[i+1] == 0 )
                {   char ch =  0xFF;
                   // newbuffer[newpos++] = (byte) 0xFF;
                   newbuffer[newpos++] = ch;
                    i++;
                    continue;
                }

                newbuffer[newpos++] = buffer[i];
            }

            length = newpos;
            buffer = newbuffer;
           // cout << "Afia's new buffer " << newbuffer << endl;
           // for(int kk = 0; kk < tagsize; kk++){
             //   cout << (char) newbuffer[kk] << endl;
            //}
        }



    //ID3v2 frames
    //Frame Header reading code
    //version 2 header=6 bytes
    //version 3 & 4 header = 10 bytes

    //int newpos=ftell(fp);
    //cout<<newpos<<endl;
    char *framebytes=new char[10];
    //fseek(fp,1,SEEK_CUR);
    //newpos=ftell(fp);
    //cout<<newpos<<endl;

   // for (int i=0;i<10;i++)
     //   cout<<framebytes[i]<<" "<<i<<endl;

    //cout<<"\nFrame Identifier: \n";
     for (int i=0;i<4;i++)
     {
         unsigned char b=byte[i];
   //     cout  <<getBit(b,7) << getBit(b,6) << getBit(b,5) << getBit(b,4) <<
          //      getBit(b,3) << getBit(b,2) << getBit(b,1) << getBit(b,0)<<" ";

        //cout<<endl;


      //   cout<<(char)framebytes[i]<<" "<<i<<endl;
     }

  //   cout<<"\nFramesize: ";
     for (int i=4;i<8;i++)
     {
    //     cout<<(unsigned char)framebytes[i]<<" "<<i<<endl;
     }

  //    cout<<"\nFrame Flags: ";
      for (int i=8;i<9;i++)
     {
        unsigned char b=byte[i];
     //   cout  <<getBit(b,7) << getBit(b,6) << getBit(b,5) << getBit(b,4) <<
       //         getBit(b,3) << getBit(b,2) << getBit(b,1) << getBit(b,0)<<" ";
       // cout<<endl;

        if (getBit(b,7)==0)
            cout<<"Frame should be preserved"<<endl;
        else
            cout<<"Frame should be discarded"<<endl;

        if (getBit(b,6)==0)
                cout<<"Frame should be preserved"<<endl;
            else
            cout<<"Frame should be discarded"<<endl;

        if (getBit(b,5)==0)
            cout<<"Frame contents are not read only"<<endl;
        else
            cout<<"Frame contents are to be read only"<<endl;
     }

      for (int i=9;i<10;i++)
     {
        unsigned char b=byte[i];
       // cout  <<getBit(b,7) << getBit(b,6) << getBit(b,5) << getBit(b,4) <<
         //       getBit(b,3) << getBit(b,2) << getBit(b,1) << getBit(b,0)<<" ";

//        cout<<endl;

        if (getBit(b,7)==0)
            cout<<"Frame is not compressed"<<endl;
        else
            cout<<"Frame is compressed"<<endl;

        if (getBit(b,6)==0)
                cout<<"Frame is not encrypted"<<endl;
            else
            cout<<"Frame should be encrypted"<<endl;

        if (getBit(b,5)==0)
            cout<<"Frame does not contain group info"<<endl;
        else
            cout<<"Frame contains group info"<<endl;
     }



    fclose(fp);


    return 0;
    }

