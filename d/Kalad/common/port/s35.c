#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Tattoo Parlour");
    set_long("You are inside a dinghy little room, the air filled with "+
      "some unmistakably dank smell. The wooden plank walls are covered with "+
      "several pictures, most of which are bawdy-looking depictions of women "+
      "and mermaids. Several couches lie about the room, while a large sign "+
      "hangs above the far wall, past a bead curtain. Directly beneath the sign is a small, squat "+
      "counter, behind which is a squat chair.\n"+
      "A tiny plaque has been tacked onto one wall.\n");
    add_item(({"wooden plank walls","wooden walls","plank walls","walls","wall"}),
      "Made from hardwood, they look quite sturdy, despite the lack of "+
      "care for them by the present owner of this place. There is a large "+
      "hole in the wall.\n");
    add_item(({"large hole","hole"}),"Its large, probably as big as Skeever "+
      "himself, and you can't see anything within it.\n"+
      "If you're not mistaken...it sounded as if something grunted from "+
      "within the darkness.\n");
    add_item(({"darkness"}),"You can't see a thing!\n");
    add_item(({"several pictures","pictures","picture"}),"You can see "+
      "images of naked women, naked mermaids, and other such paraphernalia.\n");
    add_item(({"several couches","couches","couch"}),"Covered with nice, "+
      "plump cushions, they are probably where customers sit while waiting "+
      "for their turn. You could probably sit down on one.\n");
    add_item(({"large sign","sign"}),"It has words on it, maybe you "+
      "should read it, if you can read at all...\n");
    add_item(({"small counter","squat counter","counter"}),"A three foot "+
      "high counter at the other end of the room.\n");
    add_item(({"chair"}),"A small chair covered with wooden beads.\n");
    add_item(({"bead curtain","curtain"}),"A series of long strings of "+
      "beads has been hung across the room, forming a curtain that seperates "+
      "the couches from the counter and chair. You can still see through "+
      "it though.\n");
    add_item("plaque","@@plaque");
    add_cmd_item("plaque","read","@@plaque");
    add_exit(PORT + "s36", "east");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/tattooer");
	ob1 -> move_living("xxx", TO);
    }

}

scrub(string s)
{
    NF("Scrub what? The tattoo?\n");
    if(s!="tattoo")
	return 0;

    NF("You don't have a tattoo!\n");
    if(!present("skeeverisreallyaniceguy",TP))
	return 0;

    present("skeeverisreallyaniceguy",TP)->remove_object();

    write("You place the part of your body that has the tattoo into the "+
      "large hole in the wall.\n");
    write("Your tattoo is vigorously scrubbed off!\n");
    say(QCTNAME(TP) + " places the part of " + TP->query_possessive() + " body that has the tattoo into the large hole in the wall.\n");
    say(QCTNAME(TP) + "'s tattoo is now gone!\n");

    return 1;
}

init()
{
    ::init();
    AA(read_sign,read);
    AA(sit_down,sit);
    AA(scrub,scrub);
}

string
sign()
{
    return "\n"+
    " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"+
    " !! If me am hear, U can bye tattoo an' me put it on U. If U !!\n"+
    " !! know likem me tattoo, U can scrub it and it be gone. It  !!\n"+
    " !! stay on U til U scrub it. U kanz onwy half one tattoo at !!\n"+
    " !! a time.                                                  !!\n"+
    " !! -Skeever-                                                !!\n"+
    " !! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ !!\n"+
    " !! Oh yeah, here am what you can get:                       !!\n"+
    " !! ----------------------------------                       !!\n"+
    " !! Tattoo1 : Nice picturz of pwetty lady, no have clothes!  !!\n"+
    " !! Tattoo2 : Nice picturz of fish lady.                     !!\n"+
    " !! Tattoo3 : Youse can getem words: 'I Love Mom'.           !!\n"+
    " !! Tattoo4 : BIG, oogly, scawy snake! It scare me!          !!\n"+
    " !! Tattoo5 : Scawy bird, it hurt em snakes! ;-)             !!\n"+
    " !! Tattoo6 : Pwetty wittle flower.                          !!\n"+
    " !! Tattoo7 : Reawwy pwetty horsie with horn.                !!\n"+
    " !! Tattoo8 : Feloshus bwack cat! It killem lots.            !!\n"+
    " !! Tattoo9 : Humungus dwagon...eeks!                        !!\n"+
    " !! Tattoo10: Dead head wit crossed bones.                   !!\n"+
    " !! Tattoo11: A sheelz an cwub.                              !!\n"+
    " !! Tattoo12: Two ackses over um map.                        !!\n"+
    " !! Tattoo13: Big woulden ship, it float!                    !!\n"+
    " !! Tattoo14: Reawwy beeeg fishy, it float too!              !!\n"+
    " !! Tattoo15: It sun, but no bright, it dark.                !!\n"+
    " !! Tattoo16: It magick birdie. Calls feenicks.              !!\n"+
    " !! Tattoo17: It tattoo for Nities of Somnia.                !!\n"+
    " !! Tattoo18: Dis embum of Gonedoor.                         !!\n"+
    " !! Tattoo19: Dis embum of Arnor.                            !!\n"+
    " !! Tattoo20: Theez eez embum of Itshillyinum.               !!\n"+
    " !! Tattoo21: Thiz um tattoo fer Mysties.                    !!\n"+
    " !! Tattoo22: It bunchem scawy wolfies.                      !!\n"+
    " !! ________________________________________________________ !!\n"+
    " !! Each tattoo costs 1 gold coin.                           !!\n"+
    " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"+
    " ##############################################################\n";
}

int
sit_down(string str)
{
    if(!str || str != "down")
    {
	notify_fail("Sit where, down?\n");
	return 0;
    }

    write("You sit down on a couch with an audible PLOP.\n");
    say(QCTNAME(TP) + " sits down on a couch with an audible PLOP.\n");
    set_alarm(3.0,0.0,"resting");
    return 1;
}

void
resting()
{
    write("You feel relaxed and refreshed from resting on the couch.\n");
    say(QCTNAME(TP) + " looks relaxed and refreshed from resting on the couch.\n");
    return;
}

plaque()
{
    return "\n"+
    "Written in flowing script (obviously not by Skeever) is the following:\n"+
    "Before purchasing a new tattoo, it is recommended that you 'scrub' "+
    "the old one off first.\n";
}

