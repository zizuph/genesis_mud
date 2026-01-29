#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

inherit FOREST_IN;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Eastern wing of a forsaken temple.\n" +
        "A statue of a beautiful blind female oracle");
    set_long("@@long_descr");
    
    add_item(({"statue","statue of a beautiful blind " +
                "female oracle"}),
        "You get a feeling of peace and tranquility as you " +
        "look upon this statue of a blind female oracle. " +
        "Depicting a woman of fine features and untouched " +
        "youth, you can almost imagine priests praying for " +
        "guidance before her.\n");
    add_item("eastern wall","This wall is much like the other " +
        "walls, of grey marble, once exquisitely carved, " +
        "yet what it portrayed has long been erased by the hand " +
        "of time. A statue stands before it.\n");
    add_item(({"eastern wing","wing","temple","room"}),
        "@@long_descr");
    add_item("passageway","A passageway leads out to the west.\n");
    
    add_exit(CROOM + "temp3","west",0);
    
    add_cmd_item(({"for guidance","to statue"}),"pray","@@pray");
    add_cmd_item(ANSWER,"whisper","@@answer");
    
    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in the eastern wing of a forsaken " +
    "temple. Near the eastern wall stands a statue of a " +
    "beautiful blind female oracle. Unlike everything else " +
    "of the temple, this statue seems untouched by time. " +
    "Apart from the statue, there is little else of interest " +
    "in this room. A passageway leads out to the west.\n";
}

string
pray()
{
    say(QCTNAME(TP) + " prays for guidance before the " +
        "statue of a beautiful blind female oracle.\n");
    write("You pray for guidance before the statue.\n\n\n" +
        "Your vision begins to blur...\n\n\n" +
        "Before you appears a vision of the beautiful female " +
        "oracle!\n\n" +
        "The beautiful blind female oracle smiles serenely at " +
        "you.\n\n" +
        "The beautiful blind female oracle says: Greetings mortal. " +
        "You honour me with your prayers. Thus far you have " +
        "passed the Tests of Wisdom and Faith, and your goal is " +
        "almost in sight. I will send you on your way to your " +
        "final test, that of the Mind, once you " +
        "whisper the answer to this " +
        "simple riddle...\n\n\n");
    write("     'Two bodies have I \n" +
        "     Though both joined in one \n" +
        "     The more still I stand \n" +
        "     The quicker I run.'\n\n\n" +
        "The vision of the beautiful blind female oracle " +
        "disappears.\n");
    return "";
}

string
answer()
{
    write("You whisper the answer under your breath...\n");
    say(QCTNAME(TP) + " whispers something under " +
        POSSESSIVE(TP) + " breath.\n");
    write("You hear in your head the voice of the beautiful " +
        "blind oracle: You have answered correctly. I shall " +
        "now send you on your way. Good fortune mortal!\n");
    write("You are surrounded by a bright light, and suddenly " +
        "find yourself no longer in the temple!\n");
    say(QCTNAME(TP) + " suddenly begins to glow with a " +
        "bright golden light, and then vanishes!\n");
    TP->move_living("M",MAZE + "a1",1,0);
    clone_object(FOBJ + "wand")->move(TP);
    write("A shiny wand magically appears in your possession!\n");
    return "";
}
