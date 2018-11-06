
//package mp3_frame;

import java.awt.EventQueue;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;

import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JFileChooser;

import java.awt.Color;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.awt.event.ActionEvent;

public class MainFrame {

	public JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainFrame window = new MainFrame();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public MainFrame() {
		initialize();

	}

	/**
	 * Initialize the contents of the frame.
	 */

	private void initialize() {
		frame = new JFrame();
		frame.getContentPane().setBackground(Color.DARK_GRAY);
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);

		JLabel lblNewLabel = new JLabel("MP3 EDITOR");
		lblNewLabel.setForeground(Color.ORANGE);
		lblNewLabel.setFont(new Font("Tahoma", Font.BOLD, 18));
		lblNewLabel.setBounds(156, 11, 122, 52);
		frame.getContentPane().add(lblNewLabel);

		JButton btnC = new JButton("Trim Manager");

		btnC.setFont(new Font("Tahoma", Font.BOLD, 14));
		btnC.setBounds(10, 83, 150, 37);
		frame.getContentPane().add(btnC);

		JButton button = new JButton("Merge Manager");
		button.setFont(new Font("Tahoma", Font.BOLD, 14));
		button.setBounds(10, 131, 150, 37);
		frame.getContentPane().add(button);

		JButton button_1 = new JButton("ID3v1 Manager");
		button_1.setFont(new Font("Tahoma", Font.BOLD, 14));
		button_1.setBounds(10, 179, 150, 37);
		frame.getContentPane().add(button_1);

		JButton button_2 = new JButton("ID3v2 Manager");
		button_2.setFont(new Font("Tahoma", Font.BOLD, 14));
		button_2.setBounds(249, 83, 175, 37);
		frame.getContentPane().add(button_2);

		JButton button_3 = new JButton("Frame Info Displayer");
		button_3.setFont(new Font("Tahoma", Font.BOLD, 14));
		button_3.setBounds(249, 131, 175, 37);
		frame.getContentPane().add(button_3);

		JButton btnExit = new JButton("Exit");
		btnExit.setFont(new Font("Tahoma", Font.BOLD, 14));
		btnExit.setBounds(180, 200, 114, 50);
		frame.getContentPane().add(btnExit);

		btnC.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				JOptionPane.showMessageDialog(null, "Enter a mp3 file");
				JButton open = new JButton();
				JFileChooser fc = new JFileChooser();
				// fc.setCurrentDirectory(new
				// java.io.File("C:/Users/R/Desktop"));
				fc.setDialogTitle("CHOOSER WINDOW");
				if (fc.showOpenDialog(open) == JFileChooser.APPROVE_OPTION) {

				}
				// fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				String firstRange = JOptionPane.showInputDialog("Enter the First Range: ");
				String secondRange = JOptionPane.showInputDialog("Enter the Second Range: ");

				System.out.println(fc.getSelectedFile().getAbsolutePath());
				String filePath = fc.getSelectedFile().getAbsolutePath();
				String destination = JOptionPane.showInputDialog("Enter the destination file");
				try {
					ProcessBuilder builder = new ProcessBuilder("cut.exe", filePath, destination, firstRange,
							secondRange);
					Process process = builder.start();
					InputStream inputStream = process.getInputStream();
					BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream), 1);
					String line;
					while ((line = bufferedReader.readLine()) != null) {
						System.out.println(line);
					}
					System.out.println("Done\n");
					inputStream.close();
					bufferedReader.close();
				} catch (Exception ioe) {
					// ioe.printStackTrace();
				}

			}
		});

		button.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				JButton open = new JButton();
				JFileChooser fc = new JFileChooser();
				// JOptionPane.showMessageDialog(null, "Enter the destination
				// file");

				String destiny = JOptionPane.showInputDialog("Enter the name of the destination file");
				String files = JOptionPane.showInputDialog("Enter the number of MP3 Files you want to merge.");
				// fc.setCurrentDirectory(new
				// java.io.File("C:/Users/R/Desktop"));
				int num = Integer.parseInt(files);

				for (int i = 0; i < num; i++) {
					fc.setDialogTitle("CHOOSER WINDOW");
					JOptionPane.showMessageDialog(null, "Enter the " + (i + 1) + "th  file");

					if (fc.showOpenDialog(open) == JFileChooser.APPROVE_OPTION) {

					}
					String file = fc.getSelectedFile().getAbsolutePath();
					ProcessBuilder builder = null;
					try {
						if (i == 0) {
							builder = new ProcessBuilder("merge.exe", "1", destiny, file);
						}

						else {
							builder = new ProcessBuilder("merge.exe", "2", destiny, file);
						}
						Process process = builder.start();
						InputStream inputStream = process.getInputStream();
						BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream), 1);
						String line;
						while ((line = bufferedReader.readLine()) != null) {
							System.out.println(line);
						}
						System.out.println("Done\n");
						inputStream.close();
						bufferedReader.close();
					} catch (Exception ioe) {
						// ioe.printStackTrace();
					}

				}

			}

		});
		
		button_1.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				JButton open = new JButton();
				JOptionPane.showMessageDialog(null, "Enter a mp3 file");
				JFileChooser fc = new JFileChooser();

				fc.setDialogTitle("CHOOSER WINDOW");
				if (fc.showOpenDialog(open) == JFileChooser.APPROVE_OPTION) {

				}
				String file = fc.getSelectedFile().getAbsolutePath();

				ProcessBuilder builder = new ProcessBuilder("id3v1.exe", file);
				Process process = null;
				try {
					process = builder.start();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				InputStream inputStream = process.getInputStream();
				BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream), 1);
				String line;
				try {
					while ((line = bufferedReader.readLine()) != null) {
						System.out.println(line);
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println("Done\n");
				try {
					inputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				try {
					bufferedReader.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

		});

		button_2.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				JButton open = new JButton();
				JOptionPane.showMessageDialog(null, "Enter a mp3 file");
				JFileChooser fc = new JFileChooser();

				fc.setDialogTitle("CHOOSER WINDOW");
				if (fc.showOpenDialog(open) == JFileChooser.APPROVE_OPTION) {

				}
				String file = fc.getSelectedFile().getAbsolutePath();

				ProcessBuilder builder = new ProcessBuilder("id3v2.exe", file);
				Process process = null;
				try {
					process = builder.start();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				InputStream inputStream = process.getInputStream();
				BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream), 1);
				String line;
				try {
					while ((line = bufferedReader.readLine()) != null) {
						System.out.println(line);
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println("Done\n");
				try {
					inputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				try {
					bufferedReader.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

		});
		
		button_3.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				JButton open = new JButton();
				JOptionPane.showMessageDialog(null, "Enter a mp3 file");
				JFileChooser fc = new JFileChooser();

				fc.setDialogTitle("CHOOSER WINDOW");
				if (fc.showOpenDialog(open) == JFileChooser.APPROVE_OPTION) {

				}
				String file = fc.getSelectedFile().getAbsolutePath();

				ProcessBuilder builder = new ProcessBuilder("frame.exe", file);
				Process process = null;
				try {
					process = builder.start();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				InputStream inputStream = process.getInputStream();
				BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream), 1);
				String line;
				try {
					while ((line = bufferedReader.readLine()) != null) {
						System.out.println(line);
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				System.out.println("Done\n");
				try {
					inputStream.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				try {
					bufferedReader.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

		});
		
		btnExit.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				frame.dispose();
	
			}
		});
	}
}
