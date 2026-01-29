/*
 * A toy doll
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>

 void
 create_object()
 {
	 set_name("doll");
	 add_name("rabbit");
	 set_pname("dolls");
	 set_adj("well-worn");
	 add_adj("grey");
	 add_adj("rabbit");
	 set_short("well-worn grey rabbit doll");
	 set_pshort("well-worn grey rabbit dolls");
	 
	 set_long("This is a cute litte rabbit doll. It's grey, but it has a few "
		+ "bald patches where it has been dragged along the ground. The rabbit "
		+ "holds a tiny carrot. It is smiling.\n");

	add_item( ({"carrot", "tiny carrot"}), "The carrot is tiny and orange. It "
		+ "has a green top. It looks cute held as it is between the rabbit's "
		+ "paws.\n");
	add_item( ({"paw", "paws"}), "The rabbit has cute little paws. They're "
		+ "holding a carrot.\n");
	add_item( ({"spot", "spots", "bare spot", "bare spots"}), 
		"By the looks of things, the child whose doll this is grabs the "
		+ "rabbit by the arm and drags it along behind her on the ground. "
		+ "So now some of the 'fur' has been rubbed away, leaving only "
		+ "fabric.\n");
	add_item("fur", "This isn't real fur. It's bits of string cleverly "
		+ "sticking out from the doll to mimic fur! Whoever made this doll "
		+ "must have spent a lot of time making it look just so.\n");

	setuid();
	seteuid(getuid());
	
	add_prop(OBJ_I_VOLUME, 100);
	add_prop(OBJ_I_WEIGHT, 200);
	add_prop(OBJ_I_VALUE, 1);
 }
 
 void
 init()
 {
	 ::init();
	 add_action("squeeze_rabbit", "squeeze");
 }
 
 //Awe, how cute, you can squeeze the rabbit.
 int
 squeeze_rabbit(string str)
 {
	  if(!strlen(str))
        {
            notify_fail("Squeeze what? The rabbit?\n");
            return 0;
        }
	if(parse_command(str, TO, "[the] [well-worn] [grey] [rabbit] 'doll' / 'rabbit' ") )
        {
			write("You squeeze the " + query_short() + " tightly, feeling "
				+ "comfort and love.\n");
			say(QCTNAME(TP) + " squeezes the " + query_short() + " tightly. "
				+ CAP(HE_SHE(TP)) + " looks like " + HE_SHE(TP) 
				+ " feels warm and loved.\n");
			return 1;
		}
	else
	{
		return 0;
	}
 }

string query_recover() 
{ 
    return MASTER + ":"; 
}
