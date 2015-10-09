import java.util.Random;
import java.util.Arrays;

public class PlayGame{

	static char[] suit= {'C','D','H','S'};
	static char[] face= {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

	public static void main(String[] args){
		int[] poker;
		poker= new int[54];
		for(int i=0;i<=53;i++){poker[i]=i;}
		shuffle(poker);
		display_card(poker);
		
	}

public static int[] shuffle(int[] poker){

			int sample_card,card;
			Random ran = new Random();
    		for(card=0; card!=54; ++card)
    		{
        		sample_card=(int)(ran.nextInt(54));
        		int temp;
    		    temp=poker[card];
    		    poker[card]=poker[sample_card];
    			poker[sample_card]=temp;
			}
			return poker;
    		}



public static class player{

	int [] hand;
	int name;
}

public static void display_card(int[] poker){
		
			
			player player_0= new player();
			player player_1= new player();
			player player_2= new player();
			player player_3= new player();

			player_0.hand= new int[14];
			player_1.hand= new int[14];
			player_2.hand= new int[13];
			player_3.hand= new int[13];

			player_0.name=0;
			player_1.name=1;
			player_2.name=2;
			player_3.name=3;

			for(int j=0;j<14;j++){
				player_0.hand[j]=poker[j];
				player_1.hand[j]=poker[j+14];
			}

			for(int j=0;j!=13;++j){
				player_2.hand[j]=poker[j+28];
				player_3.hand[j]=poker[j+41];
			}

			Arrays.sort(player_0.hand);
			Arrays.sort(player_1.hand);
			Arrays.sort(player_2.hand);
			Arrays.sort(player_3.hand);

			System.out.println("Deal cards");
			System.out.print("Player0: ");

			for(int i=0;i!=14;++i){
				if(player_0.hand[i]==0){
				System.out.print("R0 ");
				}

				else if(player_0.hand[i]==1){
					System.out.print("B0 ");
						}
				else{
					System.out.print(suit[ (player_0.hand[i]-2)%4 ]);
					System.out.print(face[ (player_0.hand[i]-2)/4]+" ");
					}
			}

			System.out.println("");

			System.out.print("Player1: ");

			for(int i=0;i!=14;++i){
				if(player_1.hand[i]==0){
				System.out.print("R0 ");
				}

				else if(player_1.hand[i]==1){
					System.out.print("B0 ");
						}
				else{
					System.out.print(suit[ (player_1.hand[i]-2)%4 ]);
					System.out.print(face[ (player_1.hand[i]-2)/4]+" ");
					}

			}
			
			System.out.println("");

			System.out.print("Player2: ");

			for(int i=0;i!=13;++i){
				if(player_2.hand[i]==0){
				System.out.print("R0 ");
				}

				else if(player_2.hand[i]==1){
					System.out.print("B0 ");
						}
				else{
					System.out.print(suit[ (player_2.hand[i]-2)%4 ]);
					System.out.print(face[ (player_2.hand[i]-2)/4]+" ");
					}

			}

			System.out.println("");

			System.out.print("Player3: ");

			for(int i=0;i!=13;++i){
				if(player_3.hand[i]==0){
				System.out.print("R0 ");
				}

				else if(player_3.hand[i]==1){
					System.out.print("B0 ");
						}
				else{
					System.out.print(suit[ (player_3.hand[i]-2)%4 ]);
					System.out.print(face[ (player_3.hand[i]-2)/4]+" ");
					}

			}

			System.out.println("");
			System.out.println("Drop cards");

			System.out.print("Player0: ");
			player_0.hand=drop_cards(player_0.hand);
			show_card(player_0);
			System.out.println("");

			System.out.print("Player1: ");
			player_1.hand=drop_cards(player_1.hand);
			show_card(player_1);
			System.out.println("");

			System.out.print("Player2: ");
			player_2.hand=drop_cards(player_2.hand);
			show_card(player_2);
			System.out.println("");

			System.out.print("Player3: ");
			player_3.hand=drop_cards(player_3.hand);
			show_card(player_3);
			System.out.println("");


			System.out.println("Game start");

			player[] deck={player_0,player_1,player_2,player_3};

			int i=0;
			while(the_no_of_card_is_zero(deck)){
					deal_with_card(deck,i);
				i++;			
			}
			System.out.println("Basic game over");

			//bonus part~
			player[] tempArray1,tempArray2;
			System.out.println("Continue");
			int no_of_hand=0;
			for(int j=0;j<deck.length;j++){
				if(((deck[j]).hand).length!=0){
					no_of_hand++;
				}
			}
			int total=0;
			player[] tempArray= new player[no_of_hand];
			for(int w=0;w<deck.length;w++){
				if((deck[w].hand).length!=0){
					tempArray[total]=deck[w];
					total++;
				}

			}

			int ii=0;
			while(the_no_of_card_is_zero(tempArray)){
				deal_with_card(tempArray,ii);
				ii++;
			}


			//step3
			int judge=0;
			for(int u=0;u<tempArray.length;u++){
				if((tempArray[u].hand).length!=0){
					judge++;
				}
			}
			if(judge!=1){
					no_of_hand=0;
					for(int j=0;j<tempArray.length;j++){
						if(((tempArray[j]).hand).length!=0){
							no_of_hand++;
						}
					}
					int total1=0;
					tempArray1= new player[no_of_hand];
					for(int w=0;w<tempArray.length;w++){
						if((tempArray[w].hand).length!=0){
							tempArray1[total1]=tempArray[w];
							total1++;
						}
					}

					int iii=0;
					while(the_no_of_card_is_zero(tempArray1)){
						deal_with_card(tempArray1,iii);
						iii++;
					}

			//step4
				int judge2=0;
					for(int u=0;u<tempArray1.length;u++){
						if((tempArray1[u].hand).length!=0){
							judge2++;
						}
					}

					if(judge2!=1){
						no_of_hand=0;
							for(int j=0;j<tempArray1.length;j++){
								if(((tempArray1[j]).hand).length!=0){
									no_of_hand++;
								}
							}
						int total2=0;
						tempArray2= new player[no_of_hand];
						for(int w=0;w<tempArray1.length;w++){
								if((tempArray1[w].hand).length!=0){
									tempArray2[total2]=tempArray1[w];
									total2++;
								}

						}

						int iiii=0;
						while(the_no_of_card_is_zero(tempArray2)){
								deal_with_card(tempArray1,iiii);
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

	
public static int[] drop_cards(int[] player){
	Arrays.sort(player);
	int index;
	int counter;
	int[] after_player;
		if(player[0]==0&&player[1]!=1){
			player[0]=0;
			counter=1;
			index=1;
				while(counter<player.length-1){
					if(face[ (player[counter+1]-2)/4]==face[ (player[counter]-2)/4]){
						counter=counter+2;
					}
					else{
						player[index++]=player[counter];
						counter++;
			    	}

				}
				
				if(counter==player.length-1){
					player[index++]=player[counter];
				}

		}
			
		else if(player[0]==1){
			player[0]=1;
			counter=1;
			index=1;
				while(counter<player.length-1){
					if(face[ (player[counter+1]-2)/4]==face[ (player[counter]-2)/4]){
					counter=counter+2;
					}
					else{
						player[index++]=player[counter];
						counter++;
			    	}
				}

				if(counter==player.length-1){
					player[index++]=player[counter];
				}

		}
			
		else if(player[0]==0 && player[1]==1){
				player[0]=0;
				player[1]=1;
				counter=2;
				index=2;
				while(counter<player.length-1){
					if(face[ (player[counter+1]-2)/4]==face[ (player[counter]-2)/4]){
					counter=counter+2;
					}
					else{
					player[index++]=player[counter];
					counter++;
			    	}
				}
			
				if(counter==player.length-1){
					player[index++]=player[counter];
				}

		}

		else{
				counter=0;
				index=0;
				do{
					if(face[ (player[counter+1]-2)/4]==face[ (player[counter]-2)/4]){
					counter=counter+2;
					}
					else{
					player[index++]=player[counter];
					counter++;
			    	}
				}while(counter<player.length-1);

				if(counter==player.length-1){
					player[index++]=player[counter];
				}
			}

			

	after_player=new int[index];
		for(int i=0;i!=index;++i){
			after_player[i]=player[i];
			}

			return after_player;
		}

	public static int draw_card(int[] playerA,int[] playerB){
	int newCardNo,newCard;
	Random ran = new Random();
		newCardNo=(int)(ran.nextInt(playerB.length));
		newCard=playerB[newCardNo];
	return newCard;

}

public static int[] add_card(int[] player,int newCard){
	int no=player.length;
	int[] temp;
	temp=new int[no];
	for(int i=0;i<no;i++){
		temp[i]=player[i];
	}
	player=new int[no+1];
	for(int i=0;i<no;i++){
		player[i]=temp[i];
	}
	player[no]=newCard;
	return player;
}
public static int[] sub_card(int[] player,int card){
	int index=0;
	int number=player.length;
	int[] temp;
	temp=new int[number-1];
	for(int i=0;i<=number-1;i++){
		if(player[i]!=card){
			temp[index++]=player[i];
		}
	}

	player=new int[index];
	for(int i=0;i<index;i++){
		player[i]=temp[i];
	}

	return player;
}
public static void show_card(player player1){
	Arrays.sort(player1.hand);
	for(int i=0;i<(player1.hand).length;i++){
				if(player1.hand[i]==0){
				System.out.print("R0 ");
				}

				else if(player1.hand[i]==1){
					System.out.print("B0 ");
						}
				else{
					System.out.print(suit[ (player1.hand[i]-2)%4 ]);
					System.out.print(face[ (player1.hand[i]-2)/4]+" ");
					}
			}
}


public static void show_card_comment(int newCard, int i, player[] deck,int k){
				if(newCard==0){
					System.out.println("Player"+deck[i%k].name+" draws a card from Player"+deck[((i+1)%k)].name+" R0");
				}

				else if(newCard==1){
					System.out.println("Player"+deck[i%k].name+" draws a card from Player"+deck[((i+1)%k)].name+" B0");
						}
				else{
					System.out.println("Player"+deck[i%k].name+" draws a card from Player"+deck[((i+1)%k)].name+" "+suit[ (newCard-2)%4]+face[ (newCard-2)/4] );
					}
			}

public static boolean the_no_of_card_is_zero(player[] deck){
	boolean flag=true;
	for(int i=0;i<deck.length;i++){
		if((deck[i].hand).length==0){
			flag=false;
		}
		
	}
	return flag;
}



public static void result(player a, player b, int index_a,int index_b){
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


			

public static void deal_with_card(player[] deck,int i){
	int newCard;
	int k=deck.length;
	newCard=draw_card(deck[i%k].hand,deck[((i+1)%k)].hand);
	deck[i%k].hand=add_card(deck[i%k].hand,newCard);
	deck[((i+1)%k)].hand=sub_card(deck[((i+1)%k)].hand,newCard);
	deck[i%k].hand=drop_cards(deck[i%k].hand);
	show_card_comment(newCard,i,deck,k);
	System.out.print("Player"+deck[i%k].name+": ");
	show_card(deck[i%k]);
	System.out.println("");
	System.out.print("Player"+deck[((i+1)%k)].name+": ");
	show_card(deck[((i+1)%k)]);
	System.out.println("");
	result(deck[i%k],deck[((i+1)%k)],deck[i%k].name,deck[((i+1)%k)].name);

}

}