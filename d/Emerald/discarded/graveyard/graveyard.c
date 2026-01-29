 
/*
 * The graveyard for the flowers quest.
 *
 *          &Napture.
 * Review made by Rohim 951023. (Remeber to change the def in
 * ~Emerald/wroad/obj/flower.c if you move this room.)
 *
 */

/*
 * Touched up and re-described by Alaron July 29, 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Lonely Graveyard");
    set_long("   This section of the graveyard is separated from the "+
	     "rest of the graveyard by strategic placement of the other "+
	     "headstones and small hills which rise this clearing above "+
	     "the rest of the damp, fog-covered field. Leaning slightly, "+
	     "in the middle of the cleared-out grave site stands a tall, "+
	     "lone headstone marking a grave nearly hidden by overgrown "+
	     "grass. This place seems miraculously free of the looming, "+
	     "heavy fog which casts a depressing, lonely feeling upon "+
	     "the rest of the graveyard. It is almost as if something "+
	     "here is keeping the fog and the sense of dread away.\n\n");
   
    add_exit( GRAVEYARD_DIR + "graveyard1", "west", 0);
    
    add_item("grass", "The grass is beginning to take over this part " +
                      "of the graveyard. It would appear to have not been "+
                      "cut for some time now. Strangely enough, the grass "+
                      "doesn't encroach upon the lone grave standing here."+
                      "\n");
    add_item(({"grave", "lone grave"}), "The lone grave looks as though "+
	     "it has been looked after for many a year. Despite the slightly " +
	     "overgrown grass surrounding, there are no weeds or grass on " +
	     "the grave itself. The headstone of the grave stands bold and "+
	     "upright, defying the corrosion and beatings from nature.\n");
    add_item(({"stone", "headstone", "head stone", "name stone"}),
	     "The headstone stands upright despite the many years that it " +
	     "would appear to have stood here. There is a small inscription "+
	     "written on the stone itself.\n");
    add_cmd_item(({"inscription", "writing", "writting", "epitaph"}),
		 ({"read"}), ({"@@inscrip_read"})); /* Well, *I* can't speel!! ;-) */
    add_item(({"inscription", "writing", "writting", "epitaph"}),
        "@@inscrip_descrip");
}
 
inscrip_read()
{
    write("The inscription declares this as the grave of Lady Allenia. "+
	  "It would appear the her husband cared very much for her, as "+
	  "all the old dried out flowers have been taken away. However, "+
	  "there aren't any new, fresh flowers, so perhaps something " +
	  "is wrong?\n");
    tell_room(TO, QCTNAME(TP) + " reads the inscription on the head stone.\n",
              TP);
    return 1;
}

inscrip_descrip()
{
    tell_room(TO, QCTNAME(TP) + " looks closely at the epitaph on the " +
              "head stone.\n", TP);
    return 
       "\n                  ________________	    \n" +
        "                 /                \\     \n" +
	"                /                  \\    \n" +
        "               '   Here lieth the   `    \n" +
	"               |  body of the late  |    \n" +
	"               |                    |    \n" +
	"               |    Lady Allenia    |    \n" +
	"               |                    |    \n" +
        "               |  Devoted wife and  |    \n" +
        "               |/    friend  of     /    \n" +
        "              \\/    Sir Quarloss /  \\/ \n" +
        "             \\/|    /           /   |\\  /\n" +
        "            \\ \\|/  / \\ /  \\     \\   |/  \\\n\n";
}
 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->query_npc())  {
        tell_room(TO, QCTNAME(ob) +
		  " senses a strange presence in the air!\n", ob);
        ob->command("west");
    }
    else
        set_alarm( 5.0,0.0,"presence", ob);
}

presence(object ob)
{
    object who;
 
    if (who = present(ob, TO))  {
        tell_object(who, "You sense that a strange presence is watching " +
		    "this place.\n");
    }
}
 












