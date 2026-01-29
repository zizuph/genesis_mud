inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/*
 * Guild is closed and not returning.
 * New racial was opened in Faerun.
 * 	- Lucius, June 2017
 */
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_M_NO_TELEPORT,1);
    set_short("The base of the Tower of Undraeth");
    set_long("A wedge-shaped alcove has been cut into the vast "+
      "cavern wall, forming a small plateau at the base of it. "+
      "Directly above, the tip of a gigantic stalactite looms menacingly. "+
      "From this vantage point you can see the entire city of Undraeth, " +
      "vast, concave cavern walls cradling a sparkling panorama of faerie "+
      "fires burning in the inky black. You can see the sculpted stalagmite " +
      "compounds of the Noble Houses vying for reach toward the cavern ceiling. " +
      "The winding streets that weave through the city are barely visible from "+
      "here, identifiable only as cracks between the compounds, streaked " +
      "with reddish-orange fires in places. Across the cavern is the larger "+
      "plateau of Undraeth; the city floor seems to slope up toward it from the "+
      "central chasm and the brightly pool of faerie fire at the southern lip "+
      "of it where the marketplace is located.\n"+
      "A single blood red column of light emanates from the "+
      "ground, rising meters up to the very tip of the massive "+
      "stalactite.\n");
    add_item(({"large semi-circular alcove", "large alcove", "semi-circular alcove", "alcove"}),
      "A wedge-shaped gash carved into the side of the stalagmite, " +
      "near where it meets the cavern wall.\n");
    add_item(({"massive cavern walls","massive walls","cavern walls","walls","wall"}),
      "They surround the city of Undraeth, rising through unpenetrable darkness "+
      "toward an unseeable ceiling.\n");
    add_item(({"city","undraeth"}),
      "A twisted collection of magically enhanced stalagmite and stalactite "+
      "structures surrounded by dark cavern rock.\n");
    add_item(({"twinkling lights","lights","light","faerie fire","fire"}),
      "The varying colors of magical light can be seen interspersed among "+
      "the many twisting streets of the city.\n");
    add_item(({"twisting streets","streets","street"}),
      "They wind through the city, looping around the stalagmite "+
      "buildings, and along the cavern walls.\n");
    add_item(({"blood red column of light","blood red light","red light","light","column"}),
      "A roughly man-sized beam of red hue that begins here and rises up "+
      "dozens of feet to the tip of an immense stalactite hanging from the "+
      "ceiling of this cavern.\n");
    add_item(({"ceiling"}),
      "It is shrouded in darkness.\n");
    add_item(({"ground"}),
      "It is so incredibly smooth that your reflection is clearly "+
      "visible.\n");
    add_item(({"reflection"}),
      "You see yourself.\n");
    add_item(({"stalactite", "massive stalactite"}),
      "A stalactite of massive proportions, apparently well over forty feet "+
      "in diameter.\n");
    add_item(({"steps"}),
      "A grand series of wide, well-spaced steps that leads down to the city "+
      "in the south.\n");

    add_exit(CPASS(drow/d27),"south");
    add_exit(CPASS(drow/guild/entrance), "up", "@@guard_block", 0, -1);
    set_noshow_obvious(1);
    set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(CPASS(drow/npc/guard_spider));
	ob1 -> move_living("M",TO);
    }
    if(!ob2)
    {
	ob2 = clone_object(CPASS(drow/npc/guard_spider));
	ob2 -> move_living("M",TO);
	tell_room(TO,"An aura of immense magic permeates the room upon the "+
	  "arrival of the guardian spiders.\n");
	tell_room(TO,"From a dark, choking fog emerge two guardian spiders.\n");
	tell_room(TO,"The spiders seem to stand protectively around the blood red "+
	  "column of light.\n");
	ob1 -> team_join(ob2);
    }
}
int
guard_block()
{
    if((present(ob1,TO) || present(ob2,TO)) &&
      TP->query_subloc_obj("drow_subloc") ==0)
    {
	write("You are stopped by the guardian spider!\n");
	say(QCTNAME(TP) + " tries to go up into the blood red column of light, but "+
	  "is stopped by the guardian spider!\n");
	return 1;
    }
    else
    {
	write("You step into the blood red column of light "+
	    "but nothing happens.\n");
	say(QCTNAME(TP) + " steps into the blood red column of light "+
	    "but nothing happens.\n");
	return 1;
    }
}
