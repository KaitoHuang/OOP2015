import Pocker.util.Card;
import Pocker.util.Shuffler;
import Pocker.util.Hand;

import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;
public class POOCasino{
	public static void main(String[] args){
		
		int round=1;
		int money=1000;
		int bet=1;
		Scanner scanner =new Scanner(System.in);
		String username;
		System.out.println("POOCasino Jacks or better, written by b03901156 ");
		System.out.print("Please enter your name: ");
		username=scanner.next();
		System.out.println("Welcome, "+username+".");
		System.out.println("You have 1000 P-dollars now.");
		System.out.println("");

	for(int count=1;count>0;count++){
		Shuffler deck =new Shuffler();
		Hand hand=new Hand(deck);
		System.out.print("Please enter your P-dollar bet for round "+round+" (1-5 or 0 for quitting the game): ");
		bet=scanner.nextInt();
		if(bet==0){
			System.exit(1);
		}
		System.out.print("Your cards are ");
		for(int i=0;i<5;i++)
		{
			hand.display_card(i);
		}
		System.out.println("");
		System.out.print("Which cards do you want to keep? ");
		String choose;
		choose=scanner.next();
		System.out.print("Okay. I will discard ");

		if (choose.indexOf("a") == -1){
			System.out.print("(a) "+hand.card[0]+" ");
			hand.card[0]=deck.draw_from_deck();
		} 
		if (choose.indexOf("b") == -1){
			System.out.print("(b) "+hand.card[1]+" ");
			hand.card[1]=deck.draw_from_deck();
		} 
		if (choose.indexOf("c") == -1){
			System.out.print("(c) "+hand.card[2]+" ");
			hand.card[2]=deck.draw_from_deck();
		} 
		if (choose.indexOf("d") == -1){
			System.out.print("(d) "+hand.card[3]+" ");
			hand.card[3]=deck.draw_from_deck();
		}
		if (choose.indexOf("e") == -1){
			System.out.print("(e) "+hand.card[4]+" ");
			hand.card[4]=deck.draw_from_deck();
		}  
		System.out.println("");
		System.out.print("Your new cards are ");
		for(int i=0;i<5;i++)
		{
			hand.display_card(i);
		}
		System.out.println("");
		System.out.print("You get ");
		hand.display_result();
		if(hand.value*bet==2500){
			System.out.println(" The payoff is 2500.");
			money=money-bet+2500;
		}
		else{
			System.out.println(" The payoff is "+hand.value*bet+".");
			money=(money-bet+hand.value*bet);
		}
		System.out.println("You have "+money+" P-dollars now.");
		round++;
		System.out.println("");
	}
		}	

}
