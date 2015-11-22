import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class Card{
		private String[] suits = {"C","D","H","S","R","B"};
		private String[] faces= {"2","3","4","5","6","7","8","9","10","J","Q","K","A","0"};

		protected int suit,face;
		public String faces_to_string(int _faces){
			return faces[_faces];
		}
		Card(){}

		Card(int suit,int face){
			this.suit=suit;
			this.face=face;
		}
		public @Override String toString()
    	{
          return suits[suit]+faces[face];
    	}

		public int getsuit(){
			return suit;
		}
		public int getface(){
			return face;
		}

	}