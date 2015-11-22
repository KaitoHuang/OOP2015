import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class cardDealer{
	public Card draw_card(Card[] hand_A,Card[] hand_B){
	int newCardNo;
	Card newCard;
	Random ran = new Random();
		newCardNo=(int)(ran.nextInt(hand_B.length));
		newCard=hand_B[newCardNo];
	return newCard;
	}

	public Card[] add_card(Card[] hand,Card newCard){
		int no=hand.length;
		Card[] temp;
		temp=new Card[no];
		for(int i=0;i<no;i++){
			temp[i]=hand[i];
		}
		hand=new Card[no+1];
		for(int i=0;i<no;i++){
			hand[i]=temp[i];
		}
		hand[no]=newCard;
		return hand;
	}

	public Card[] sub_card(Card[] hand,Card card){
	int index=0;
	int number=hand.length;
	Card[] temp;
	temp=new Card[number-1];
	for(int i=0;i<=number-1;i++){
		if(hand[i]!=card){
			temp[index++]=hand[i];
		}
	}

	hand=new Card[index];
	for(int i=0;i<index;i++){
		hand[i]=temp[i];
	}

	return hand;
	}

	public void show_card(Player player){
	player.sort_cards(player.hand);
	for(int i=0;i<(player.hand).length;i++){
				player.display_card(i);
			}
	}
	public void show_card_comment(Card newCard, int i, Player[] player,int k){
				System.out.println("Player"+player[i%k].name+" draws a card from Player"+player[((i+1)%k)].name+" "+newCard);
	}
	public boolean the_no_of_card_is_zero(Player[] player){
	boolean flag=true;
	for(int i=0;i<player.length;i++){
		if((player[i].hand).length==0){
			flag=false;
		}
		
	}
	return flag;
	}
	public void result(Player a, Player b, int index_a,int index_b){
	if((a.hand).length==0&&(b.hand).length==0){
			System.out.println("Player"+index_a+" and Player"+index_b+" win");
		}
		else if((a.hand).length==0&&(b.hand).length!=0){
			System.out.println("Player"+index_a+" wins");
		}
		else if((a.hand).length!=0&&(b.hand).length==0){
			System.out.println("Player"+index_b+" wins");
		}
	}
	public void deal_with_card(Player[] player,int i){
	Card newCard;
	int k=player.length;
	newCard=draw_card(player[i%k].hand,player[((i+1)%k)].hand);
	player[i%k].hand=add_card(player[i%k].hand,newCard);
	player[((i+1)%k)].hand=sub_card(player[((i+1)%k)].hand,newCard);
	player[i%k].hand=player[i%k].drop_cards(player[i%k].hand);
	show_card_comment(newCard,i,player,k);
	System.out.print("Player"+player[i%k].name+": ");
	show_card(player[i%k]);
	System.out.println("");
	System.out.print("Player"+player[((i+1)%k)].name+": ");
	show_card(player[((i+1)%k)]);
	System.out.println("");
	result(player[i%k],player[((i+1)%k)],player[i%k].name,player[((i+1)%k)].name);

	}
}