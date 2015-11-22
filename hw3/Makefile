JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
		$(JC) $(JFLAGS) $*.java

CLASSES = \
		Card.java \
		Shuffler.java \
		Player.java \
		cardDealer.java \
		Computer.java \
		Oldmaid_Game.java \
		Oldmaid_Game_variant_1.java \
		Oldmaid_Game_variant_2.java \
		Game.java 

default: classes
	

classes: $(CLASSES:.java=.class)

clean:
		$(RM) *.class