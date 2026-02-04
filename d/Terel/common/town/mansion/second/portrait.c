
/* Portrait of the Marquis de Avenchir    Napture */
        
inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)	break_string(message,70)
#define TP              this_player()
#define TO              this_object()

init()
{
    ::init();
    add_action("do_tear", "tear");
    add_action("do_tear", "rip");
    add_action("do_tear", "slice");
    add_action("do_tear", "cut");
    add_action("do_clean", "clean");
    add_action("do_clean", "wipe");
}

create_object()
{
    set_name(({"portrait", "painting"}));
    add_adj(({"magnificent", "huge", "west", "western"}));
    set_short("magnificent portrait, almost covering the entire wall.");
    set_pshort("huge portraits.  You suspect they are fakes.");
    set_long(
"This huge painting almost covers the entire western wall.  The prominent\n"+
"figure of this portrait is a tall man, with fresh young features, short\n"+
"brown hair and attractive green eyes.  He is holding a pleasant        \n"+
"expression as he gazes down at you.  The man holds an ornate walking    \n"+
"stick in his left hand, while his right arm is held across the shoulders\n"+
"of a huge silver coated wolf.  The wolf is indeed huge; his shoulders  \n"+
"stand almost up to the man's chest.  He has fangs the size of a man's  \n"+
"head, yet his dark green eyes gaze down at you as peacefully as his    \n"+
"companion's.  Despite the obvious size and power of these two, their   \n"+
"friendly gazes make you feel very comfortable.                         \n"+
"A small plaque made from black marble has inscribed on it :            \n"+
"'The Marquis de Avenchir.'                                             \n"
        );
    
    add_prop(OBJ_M_NO_GET, BS("As you approach the painting to remove it " +
		"from the wall, you notice the dark green eyes of the " +
		"Marquis staring directly at you.  You feel an " +
		"overwhelming presence and for some reason you decide " +
		"that this may not be such a good idea.\n"));
}

do_clean(string str)
{
    object ob1;

    if (!str || (!parse_command(str, environment(TP), "%o", ob1))) return 0;
    if (ob1!=TO) return 0;   

    write(BS("As you start to " + query_verb() + " the portrait, " +
             "you step back in amazement :  there is not a single " +
             "speck of dust to be seen anywhere on the portrait. " +
             "Not only that, but the colours are very vivid; as " +
             "though they are freshly dry.\n"));
    say(QCTNAME(TP) + " starts to " + query_verb() + " the " +
             str + ", but suddenly stops in amazement!\n");
    return 1;    		 
}

int
do_tear(string str)
{
    string str1, str2;
    object ob1, ob2;


    notify_fail(capitalize(query_verb()) + " what?\n");
    if (!str)  return 0;
    if (sscanf(str, "%s with %s", str1, str2)!=2)  {
        if (!parse_command(str, environment(TP), "%o", ob1))  return 0;
        if (ob1!=TO)  return 0;
        write(capitalize(query_verb())+" the portrait with what?\n");
        return 1;        
    }
    if (!parse_command(str1, environment(TP), "%o", ob1))  return 0;
    if (ob1!=TO)  return 0;

    notify_fail(capitalize(query_verb()) + " the portrait with what?\n");
    if (!parse_command(str2, environment(TP), "%o", ob2))  return 0;
    if (!present(ob2, TP))  return 0;

    write(BS("As you approach the portrait preparing to " + 
        query_verb() + " it with the " + ob2->query_name() +
        ", you happen to look into the face of the Marquis.  " +
        "He appears to fix you with a freezing glance as " +
        "the hell fires rage in his eyes!\n"));
    say(QCTNAME(TP) + " foolishly attempts to " + query_verb() +
	     " the portrait.\n");
    return 1;
}
