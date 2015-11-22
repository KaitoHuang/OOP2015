import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class Player{
	protected Card[] hand;
	protected int name;
	public Player(){}
	public Player(Shuffler d,int number){
		hand=new Card[number];
		for(int i=0;i<number;i++){
			hand[i]=d.draw_from_deck();
		}
		sort_cards(hand);
	}

	public void display_card(int number){
            System.out.print(hand[number]);
            System.out.print(" ");
        }

    public void sort_cards(Card[] hand){
    	Card temp;
    	for(int k=0;k<hand.length-1;k++){
    				for(int r=k+1;r<hand.length;r++){
    					if((hand[k].getface()>hand[r].getface())||(hand[k].getface()==hand[r].getface()&&hand[k].getsuit()>hand[r].getsuit())){
    						temp=hand[k];
    						hand[k]=hand[r];
    						hand[r]=temp;

    					}			
    				}
    			}

    			if((hand.length-1>0)&&(hand[hand.length-2].getsuit()==4&&hand[hand.length-1].getsuit()==5)){
    			temp=hand[0];
    			hand[0]=hand[hand.length-2];
    			hand[hand.length-2]=temp;
    			temp=hand[1];
    			hand[1]=hand[hand.length-1];
    			hand[hand.length-1]=temp;
    			for(int k=2;k<hand.length-1;k++){
    				for(int r=k+1;r<hand.length;r++){
    					if((hand[k].getface()>hand[r].getface())||(hand[k].getface()==hand[r].getface()&&hand[k].getsuit()>hand[r].getsuit())){
    						temp=hand[k];
    						hand[k]=hand[r];
    						hand[r]=temp;

    					}			
    				}
    			}
    		}

    		else if((hand.length-1>0)&&((hand[hand.length-1].getsuit()==4)||(hand[hand.length-1].getsuit()==5))){
    			temp=hand[0];
    			hand[0]=hand[hand.length-1];
    			hand[hand.length-1]=temp;
    			for(int k=1;k<hand.length-1;k++){
    				for(int r=k+1;r<hand.length;r++){
    					if((hand[k].getface()>hand[r].getface())||(hand[k].getface()==hand[r].getface()&&hand[k].getsuit()>hand[r].getsuit())){
    						temp=hand[k];
    						hand[k]=hand[r];
    						hand[r]=temp;

    					}			
    				}
    			}
    		}
    	
    	}
    	public Card[] drop_cards(Card[] cards){
    	sort_cards(cards);
		int index;
		int counter;
		Card[] after_hand;
		if(cards[0].getsuit()==4&&cards[1].getsuit()!=5){
			cards[0]=cards[0];
			counter=1;
			index=1;
				while(counter<cards.length-1){
					if(cards[counter].getface()==cards[counter+1].getface()){
						counter=counter+2;
					}
					else{
						cards[index++]=cards[counter];
						counter++;
			    	}

				}
				
				if(counter==cards.length-1){
					cards[index++]=cards[counter];
				}

		}

		else if(cards[0].getsuit()==5){
			cards[0]=cards[0];
			counter=1;
			index=1;
			while(counter<cards.length-1){
					if(cards[counter].getface()==cards[counter+1].getface()){
						counter=counter+2;
					}
					else{
						cards[index++]=cards[counter];
						counter++;
			    	}

				}
				
				if(counter==cards.length-1){
					cards[index++]=cards[counter];
				}
		}

		else if(cards[0].getsuit()==4 && cards[1].getsuit()==5){
				cards[0]=cards[0];
				cards[1]=cards[1];
				counter=2;
				index=2;
				while(counter<cards.length-1){
					if(cards[counter].getface()==cards[counter+1].getface()){
						counter=counter+2;
					}
					else{
						cards[index++]=cards[counter];
						counter++;
			    	}
				}
			
				if(counter==cards.length-1){
					cards[index++]=cards[counter];
				}

		}

		else{
				counter=0;
				index=0;
				do{
					if(cards[counter].getface()==cards[counter+1].getface()){
						counter=counter+2;
					}
					else{
						cards[index++]=cards[counter];
						counter++;
			    	}
				}while(counter<cards.length-1);

				if(counter==cards.length-1){
					cards[index++]=cards[counter];
				}
			}

			after_hand=new Card[index];
		for(int i=0;i!=index;++i){
			after_hand[i]=cards[i];
			}

			return after_hand;

	}
 
}
