package Pocker.util;

import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;
public class Hand{
        public Card[] card;
        public int value;
        public Hand(Shuffler d){
            card=new Card[5];
            for(int i=0;i<5;i++){
                card[i]=d.draw_from_deck();
            }
        }



        public void display_card(int i){
            String[] index = {"(a)","(b)","(c)","(d)","(e)"};
            System.out.print(index[i]+" "+card[i]);
            System.out.print(" ");
        }

        public void display_result(){
            
            int[] no_of_faces=new int[14];
            for(int i=0;i<13;i++){
                no_of_faces[i]=0;
            }
            for(int j=0;j<5;j++){
                no_of_faces[card[j].getface()]++;
            }
        //

        //
           int  no_of_same_card_a=1;
            int  no_of_same_card_b=1;
            int  no_of_most_faces_a=20;
            int  no_of_most_faces_b=20;
            for(int i=0;i<13;i++){
                if(no_of_faces[i]>no_of_same_card_a)
                    {
                        if(no_of_same_card_a!=1){
                            no_of_same_card_b=no_of_same_card_a;
                            no_of_most_faces_b=no_of_most_faces_a;
                        }
                        no_of_same_card_a=no_of_faces[i];
                        no_of_most_faces_a=i;
                    }
                else if(no_of_faces[i]>no_of_same_card_b)
                    {
                        no_of_same_card_b=no_of_faces[i];
                        no_of_most_faces_b=i;
                    }
            }

        //

        //
            boolean isflush=true;
            for(int i=0;i<4;i++){
                if(card[i].getsuit()!=card[i+1].getsuit()){
                    isflush=false;
                }
            }

        //

        //
            boolean isstraight=false;
            int topValue=0;
            for(int j=0;j<9;j++){
                if(no_of_faces[j]==1&&no_of_faces[j+1]==1&&no_of_faces[j+2]==1&&no_of_faces[j+3]==1&&no_of_faces[j+4]==1){
                    isstraight=true;
                    topValue=j+4;
                    break;
                }
                if((no_of_faces[10]==1)&&(no_of_faces[11]==1)&&(no_of_faces[12]==1)&&(no_of_faces[9]==1)&&(no_of_faces[0]==1)){
                    isstraight=true;
                    topValue=1;
                }
            }

        //  

        //
            boolean is_jackorbetter=false;
            if(no_of_same_card_a==2&&no_of_same_card_b==1&&no_of_most_faces_a==0){
                is_jackorbetter=true;
            }
            if(no_of_same_card_a==2&&no_of_same_card_b==1&&no_of_most_faces_a==10){
                is_jackorbetter=true;
            }
            if(no_of_same_card_a==2&&no_of_same_card_b==1&&no_of_most_faces_a==11){
                is_jackorbetter=true;
            }
            if(no_of_same_card_a==2&&no_of_same_card_b==1&&no_of_most_faces_a==12){
                is_jackorbetter=true;
            }

        //evaluation
            if(isflush==true&&no_of_faces[9]==1&&no_of_faces[10]==1&&no_of_faces[11]==1&&no_of_faces[12]==1&&no_of_faces[0]==1)
            {
                value=250;
            }   
            else if(isflush&&isstraight)
            {   
                value=50;
            }
            else if(no_of_same_card_a==4&& no_of_same_card_b==1)
            {
                value=25;
            }
            else if(no_of_same_card_a==3&& no_of_same_card_b==2)
            {
                value=9;
            }
            else if(isflush){
                value=6;
            }
            else if(isstraight){
                value=4;
            }
            else if(no_of_same_card_a==3){
                value=3;
            }
            else if(no_of_same_card_a==2&& no_of_same_card_b==2){
                value=2;
            }
            else if(is_jackorbetter){
                value=1;
            }
            else{
                value=0;
            }


            switch(value){
                case 250: 
                    System.out.print("a royal flush.");
                    break;
                case 50:
                    System.out.print("a straight flush."); 
                    break;
                case 25:
                    System.out.print("a four of a kind."); 
                    break;
                case 9:
                    System.out.print("a full house.");  
                    break;
                case 6:
                    System.out.print("a flush."); 
                    break;
                case 4:
                    System.out.print("a straight."); 
                    break;
                case 3:
                    System.out.print("a three of a kind."); 
                    break;
                case 2:
                    System.out.print("a two pair."); 
                    break;
                case 1:
                    System.out.print("a Jacks or better.");  
                    break;
                default:
                    System.out.print("Nothing.");
            }
        }

    }           