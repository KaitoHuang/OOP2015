import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class Computer{
		Player player_0,player_1,player_2,player_3;
		public Computer(int idx){
			if(idx==0){
			Shuffler deck =new Shuffler(0);
			player_0=new Player(deck,14);
			player_1=new Player(deck,14);
			player_2=new Player(deck,13);
			player_3=new Player(deck,13);
			}
			if(idx==1){
				Shuffler deck =new Shuffler(1);
				player_0=new Player(deck,14);
				player_1=new Player(deck,13);
				player_2=new Player(deck,13);
				player_3=new Player(deck,13);
			}
			if(idx==2){
				Shuffler deck =new Shuffler(2);
				player_0=new Player(deck,13);
				player_1=new Player(deck,13);
				player_2=new Player(deck,13);
				player_3=new Player(deck,13);
			}

			player_0.name=0;
			player_1.name=1;
			player_2.name=2;
			player_3.name=3;
		}
		public void Original_cards(){
		System.out.println("Deal cards");

		System.out.print("Player0: ");
		for(int i=0;i<(player_0.hand).length;i++){
			player_0.display_card(i);
		}


		System.out.println("");

		System.out.print("Player1: ");
		for(int i=0;i<(player_1.hand).length;i++){
			player_1.display_card(i);
		}
		System.out.println("");

		System.out.print("Player2: ");
		for(int i=0;i<(player_2.hand).length;i++){
			player_2.display_card(i);
		}
		System.out.println("");

		System.out.print("Player3: ");
		for(int i=0;i<(player_3.hand).length;i++){
			player_3.display_card(i);
		}
		System.out.println("");
	}


	public void Drop_cards_first_round(){
		System.out.println("");
		System.out.println("Drop cards");

		player_0.hand=player_0.drop_cards(player_0.hand);
		player_1.hand=player_1.drop_cards(player_1.hand);
		player_2.hand=player_2.drop_cards(player_2.hand);
		player_3.hand=player_3.drop_cards(player_3.hand);

		System.out.print("Player0: ");
		for(int i=0;i<(player_0.hand).length;i++){
			player_0.display_card(i);
		}
		System.out.println("");

		System.out.print("Player1: ");
		for(int i=0;i<(player_1.hand).length;i++){
			player_1.display_card(i);
		}
		System.out.println("");

		System.out.print("Player2: ");
		for(int i=0;i<(player_2.hand).length;i++){
			player_2.display_card(i);
		}
		System.out.println("");

		System.out.print("Player3: ");
		for(int i=0;i<(player_3.hand).length;i++){
			player_3.display_card(i);
		}
	}
	public void basic_Oldmaid_game(){
		System.out.println("");

		System.out.println("Game start");

		cardDealer dealer=new cardDealer();

			Player[] player={player_0,player_1,player_2,player_3};
			int q=0;
			while(dealer.the_no_of_card_is_zero(player)){
					dealer.deal_with_card(player,q);
				q++;			
			}
			System.out.println("Basic game over");
		}







			//bonus part~
		public void Bonus_game(){
			cardDealer dealer=new cardDealer();
			Player[] player={player_0,player_1,player_2,player_3};
			Player[] tempPlayer1,tempPlayer2;
			System.out.println("Continue");
			int no_of_hand=0;
			for(int j=0;j<player.length;j++){
				if(((player[j]).hand).length!=0){
					no_of_hand++;
				}
			}
			int total=0;
			Player[] tempPlayer= new Player[no_of_hand];
			for(int w=0;w<player.length;w++){
				if((player[w].hand).length!=0){
					tempPlayer[total]=player[w];
					total++;
				}

			}

			int ii=0;
			while(dealer.the_no_of_card_is_zero(tempPlayer)){
				dealer.deal_with_card(tempPlayer,ii);
				ii++;
			}


			//step3
			int judge=0;
			for(int u=0;u<tempPlayer.length;u++){
				if((tempPlayer[u].hand).length!=0){
					judge++;
				}
			}
			if(judge!=1){
					no_of_hand=0;
					for(int j=0;j<tempPlayer.length;j++){
						if(((tempPlayer[j]).hand).length!=0){
							no_of_hand++;
						}
					}
					int total1=0;
					tempPlayer1= new Player[no_of_hand];
					for(int w=0;w<tempPlayer.length;w++){
						if((tempPlayer[w].hand).length!=0){
							tempPlayer1[total1]=tempPlayer[w];
							total1++;
						}
					}

					int iii=0;
					while(dealer.the_no_of_card_is_zero(tempPlayer1)){
						dealer.deal_with_card(tempPlayer1,iii);
						iii++;
					}

			//step4
				int judge2=0;
					for(int u=0;u<tempPlayer1.length;u++){
						if((tempPlayer1[u].hand).length!=0){
							judge2++;
						}
					}

					if(judge2!=1){
						no_of_hand=0;
							for(int j=0;j<tempPlayer1.length;j++){
								if(((tempPlayer1[j]).hand).length!=0){
									no_of_hand++;
								}
							}
						int total2=0;
						tempPlayer2= new Player[no_of_hand];
						for(int w=0;w<tempPlayer1.length;w++){
								if((tempPlayer1[w].hand).length!=0){
									tempPlayer2[total2]=tempPlayer1[w];
									total2++;
								}

						}

						int iiii=0;
						while(dealer.the_no_of_card_is_zero(tempPlayer2)){
								dealer.deal_with_card(tempPlayer1,iiii);
								iiii++;
						}
					}

				else{
					System.out.println("Bonus game over");
				}

		}
			else{
				System.out.println("Bonus game over");
			}

}
}