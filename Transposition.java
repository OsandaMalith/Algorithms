import java.util.ArrayList;
import java.util.Scanner;
/*	Transposition Encryption Program written by Osanda Malith
 * This is how it works. Let's take a small example.
 * 
 * Msg= Hello World
 * Key = 4
 * 
 *   1 2 3 4
 *  +-+-+-+-+
 *  |H|E|L|L|
 *  +-+-+-+-+
 *  |O|$|W|O|
 *  +-+-+-+-+
 *  |R|L|D|$|
 *  +-+-+-+-+
 * 
 * $ = Spaces
 * 
 * Write down each row:
 *  HORE LLWDLO
 *  
 *  This is the Java version, indeed the language is very bulky. If you know any better elegant way of
 *  writting this logic in Java let me know :)
 * 
 */

public class Transposition {
	
	private static Scanner in = new Scanner(System.in);;

	public static void main(String[] args) {
		ArrayList<String> cipher = new ArrayList<String>();
		System.out.print("Enter your message: ");
		String msg = in.nextLine();
		String text = "";
		StringBuilder txt = new StringBuilder(text);
		System.out.print("Enter your Key: ");
		int key = in.nextInt();
		for (int i = 0; i < key; i++) {
			int pointer = i;
			String msg_char = Character.toString(msg.charAt(i));
			cipher.add(msg_char);
			while (pointer < msg.length()) {
				String pointer_char = Character.toString(msg.charAt(pointer));
				txt.append(cipher.get(i).replace(msg_char, pointer_char));
				pointer += key;
			}
		} System.out.println(txt);
	}
}
