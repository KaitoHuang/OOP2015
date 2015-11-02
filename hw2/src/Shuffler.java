package Pocker.util;

import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;
public class Shuffler{
	public ArrayList<Card> cards;
	public Shuffler(){
			cards=new ArrayList<Card>();
			int sample_card,cardno;
			Random ran =new Random();
			Card temp;
			for(int i=0;i<4;i++){
				for(int j=0;j<13;j++){
					cards.add(new Card(i,j));
				}
			}

    		for(cardno=0; cardno!=52; ++cardno)
    		{
        		sample_card=(int)(ran.nextInt(cards.size()));
    		    temp=cards.get(cardno);
    		    cards.set(cardno,cards.get(sample_card));
    		    cards.set(sample_card, temp);
			}
    }

    		public int get_Sizeof_cards(){
    			return cards.size();
    		}
    		public Card draw_from_deck(){
    			return cards.remove(0);
    		}
}