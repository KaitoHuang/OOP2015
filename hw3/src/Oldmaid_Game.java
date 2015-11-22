import java.util.Random;
import java.util.Arrays;
import java.util.Scanner;
import java.util.ArrayList;

public class Oldmaid_Game{
	public Oldmaid_Game(){};
	public Computer Set(){
		Computer computer=new Computer(0);
		return computer;
	}
	public void Run(Computer computer){
	computer.Original_cards();
	computer.basic_Oldmaid_game();
	computer.Bonus_game();
	}
}