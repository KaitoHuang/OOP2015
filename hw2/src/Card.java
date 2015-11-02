package Pocker.util;
import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;
public class Card{
		private String[] suits = {"C","D","H","S"};
		private String[] faces= {"A","2","3","4","5","6","7","8","9","T","J","Q","K"};
		private int suit,face;
		public String faces_to_string(int _faces){
			return faces[_faces];
		}
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