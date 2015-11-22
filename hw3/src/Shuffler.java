import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class Shuffler{
	public ArrayList<Card> cards;
	public Shuffler(int idx){
		int sample_card,cardno;
		Card temp;
		Random ran =new Random();
		if(idx==0){
			cards=new ArrayList<Card>();
			cards.add(new Card(4,13));
			cards.add(new Card(5,13));
			for(int i=0;i<4;i++){
				for(int j=0;j<13;j++){
					cards.add(new Card(i,j));
				}
			}
		}
		if(idx==1){
			cards=new ArrayList<Card>();
			cards.add(new Card(4,13));
			for(int i=0;i<4;i++){
				for(int j=0;j<13;j++){
					cards.add(new Card(i,j));
				}
			}
		}

		if(idx==2){
			cards=new ArrayList<Card>();
			cards.add(new Card(4,13));
			cards.add(new Card(0,6));
			cards.add(new Card(1,6));
			cards.add(new Card(2,6));
			for(int i=0;i<4;i++){
				for(int j=0;j<6;j++){
					cards.add(new Card(i,j));
				}
			}
			for(int i=0;i<4;i++){
				for(int j=7;j<13;j++){
					cards.add(new Card(i,j));
				}
			}
		}

    		for(cardno=0; cardno!=cards.size(); ++cardno)
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