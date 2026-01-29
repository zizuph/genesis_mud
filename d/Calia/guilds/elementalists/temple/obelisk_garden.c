
/*
 * obelisk_garden.c
 *
 * Garden for the Spirit Circle of Psuchae Temple
 * New members to the guild will be teleported here after being
 * initiated. They can also teleport to here with the Anakalo
 * Gift. 
 *
 * Copyright (C): Jaacar (Mike Phipps), July 30th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "defs.h"

#define HE   TP->query_pronoun()
#define HIS  TP->query_possessive()
#define HIM  TP->query_objective()

public string task_lines_drawn = "";
public string task_objects_made = "";
public string long_desc;
public int task_lines_status = 0;
public int task_objects_status = 0;

public string
lines_desc()
{
	return "The black lines of dirt "+
        "and ground connect the obelisks together forming a "+
        "pentagram. "+task_lines_drawn+"\n";
}

public string
long_desc()
{
	
	long_desc = "You are standing in a holy garden of Elementals. Here "+
        "you see an amazing variety of plants, trees and flowers "+
        "growing all around you. A small path naturally curves its "+
        "way in here from the east and then forms a perfect circle "+
        "around the five obelisks in the centre of the garden. You "+
        "feel an inner peace just being in this place of magnificence "+
        "and beauty. "+task_objects_made+"\n";
    return long_desc;
}

int
update_long_desc()
{
    long_desc = "You are standing in a holy garden of Elementals. Here "+
        "you see an amazing variety of plants, trees and flowers "+
        "growing all around you. A small path naturally curves its "+
        "way in here from the east and then forms a perfect circle "+
        "around the five obelisks in the centre of the garden. You "+
        "feel an inner peace just being in this place of magnificence "+
        "and beauty. "+task_objects_made+"\n";
    return 1;
}

void
create_room()
{
    set_short("Obelisk garden");
    set_long(VBFC_ME("long_desc"));

    add_item("stones", "The stones are small white river stones, which "+
      "are covered in moss. On one stone however, the moss has been "+
      "pulled away, and you can make out black veins of color in it.\n");
    add_item("veins", "Closer examination of the veins shows that they "+
      "are etchings, masterfully designed to read:\nYou have set the "+
      "powers of the four quarters of the earth to cross each other.  "+
      "You have made me cross the good road and the road of difficulties, "+
      "and where they cross, the place is holy. Day in, day out, "+
      "forevermore, You are the life of things.\n");    
    add_item(({"first obelisk","1st obelisk","black obelisk"}),
        "At the northern most point lies the first obelisk. This "+
        "black stone obelisk represents Psuchae.\n");
    add_item(({"second obelisk","2nd obelisk","white obelisk"}), 
        "In the northwestern corner lies the second obelisk. This "+
        "white stone obelisk represents Lady Aeria.\n");
    add_item(({"third obelisk","3rd obelisk","blue obelisk"}), 
        "In the northeastern corner lies the third obelisk. This "+
        "blue stone obelisk represents Lord Diabrecho.\n");
    add_item(({"fourth obelisk","4th obelisk","brown obelisk"}), 
        "In the southwestern corner lies the fourth obelisk. This "+
        "brown stone obelisk represents Lady Gu.\n");
    add_item(({"fifth obelisk","5th obelisk","red obelisk"}), 
        "In the southeastern corner lies the fifth obelisk. This "+
        "red stone obelisk represents Lord Pyros.\n");
    add_item("pentagram","The obelisks and black lines form the "+
        "pattern of a pentagram in the centre of the garden.\n");
    add_item(({"lines","black lines","line","black line","runes"}),VBFC_ME("lines_desc"));
    add_item(({"obelisk","obelisks","five obelisks"}),"In the "+
        "centre of the path you see five obelisks. The ground is "+
        "dug up in straight lines between the obelisks forming "+
        "black lines. Each of the obelisks is made of a different "+
        "coloured stone and stands about five feet high. They look "+
        "very smooth to the touch.\n");
    add_item(({"circle","perfect circle"}),"The path forms a "+
        "perfect circle around the five obelisks, then winds "+
        "its way back to the east.\n");
    add_item(({"flower","flowers"}),"There must be at least five "+
        "hundred flowers here of every size, shape and colour "+
        "imaginable. Amoung the plants you recognize are the pansy, "+
        "the iris, the hydrangea, orchids, and the hanwi.\n");
    add_item("hanwi","Also known as wildflowers, they are an "+
        "extremely delicate white flower with four large white "+
        "petals and a much thinner and more delicate petal that "+
        "sits just behind and inbetween the larger four petals. "+
        "The white gives way to gradually darker shades of green "+
        "the closer the petal is to the stamen. They grow very "+
        "close to the ground.\n");
    add_item(({"grass","lush grass","lush grassy area"}),"The grass "+
        "is all a uniform height and looks like a perfect green "+
        "carpet covering the area. Throughout the grass are pockets "+
        "of flowers.\n");
    add_item(({"path","dirt path","small dirt path","small path"}),
        "The small path consists of reddish crushed gravel and dirt, "+
        "and it winds its way naturally off to east and forms a perfect "+
        "circle around the five obelisks.\n");
    add_item(({"plant","plants"}),"There are several types of "+
        "plants growing in this place including trees and "+
        "flowers.\n");
    add_item(({"tree","trees"}),"There are several types of trees "+
        "growing here. Of all of them that you see, you recognize "+
        "pine trees, bonsai trees and gardenia trees.\n");
    add_item(({"pine tree","pine trees"}),"These beautiful tall "+
        "pine trees, also known as evergreen trees are almost "+
        "perfectly triangular in shape. They are a deep forest "+
        "green in colour and very soft to the touch. They grow "+
        "around alot of the plants here.\n");
    add_item("pansy","The pansy orchid has large, flat blooms. "+
        "Their flowers are burgandy in colour and have an outer "+
        "edge of white with a yellow throat. Their leaves are "+
        "slender and pointed, much like an iris. The flowers have "+
        "only a few petals and are splayed out, almost looking a bit "+
        "like fingers on top with larger petals on the lower half "+
        "resembling the palm of a hand.\n");
    add_item("iris","There are irises of both blue and purple in "+
        "colour, all of them with a yellow centre, long pointed "+
        "leaves, and blooms that appear to have burst from the stem.\n");
    add_item(({"gardenia tree","gardenia trees","gardenia"}),"This small "+
        "flowering tree has large white blooms and large, oval "+
        "waxy leaves. These trees are very delicate and appear "+
        "as though someone has taken a bunch of fallen flower "+
        "petals and spread them out in a flat circle and called "+
        "it a plant. They vary in size from a hands height tall "+
        "to almost two hands height.\n");
    add_item(({"bonsai tree","bonsai trees","bonsai"}),"These diminutive "+
        "trees have a small twisting leaning trunk and branches "+
        "and tiny leaves. Each diminutive tree represents nature "+
        "in concentrated form, and no two trees are alike. They "+
        "appear to have been shaped by the currents. They are "+
        "about one and a half hands high, and have a wide, triangular "+
        "head of foliage and exaggerated width to heighth proportion. "+
        "They are surrounded by mossy stones.\n");
    add_item(({"mossy stones","mossy stone"}),"These small stones "+
        "are covered in some strange moss and surround the bonsai "+
        "trees.\n");
    add_item(({"strange moss","moss"}),"The moss is brownish-red in "+
        "colour and very strange to the touch.\n");
    add_item("hydrangea","These flowers are large, coloured blue, "+
        "and almost dome-shaped, the flat being where the stem meets "+
        "the bloom. They look as if someone has come along and pinched "+
        "merangue or frosting into a random pattern with the petals. "+
        "The leaves are your standard oval with a point shape, "+
        "slightly fuzzy, and have deep lines radiating from the centre "+
        "of the leaf to its outer edges.\n");
    add_item(({"orchid","orchids"}),"These orchids, known also as snowfrost "+
        "phalaenopsis, have the typical orchid long, broad, waxy "+
        "leaves at the base and a tall spindly stem that offers "+
        "the heavy blossoms at the top of it, all in a row. They "+
        "are light pink with a dark pink stamen and frosted outer "+
        "rims, hence the name.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(ELEMENTALIST_TEMPLE + "cliff", "east");
}

void
set_task_lines_status(int value)
{
	task_lines_status = value;
	switch(task_lines_status)
	{
		case 1:
			task_lines_drawn="There is a golden hue to the line connecting "+
			    "the black Obelisk and the brown Obelisk.";
			break;
		case 2:
			task_lines_drawn="There is a golden hue to the line connecting "+
			    "the black Obelisk, the brown Obelisk and the blue Obelisk.";
			break;
		case 3:
			task_lines_drawn="There is a golden hue to the line connecting "+
			    "the black Obelisk, the brown Obelisk, the blue Obelisk "+
			    "and the white Obelisk.";
			break;
		case 4:
			task_lines_drawn="There is a golden hue to the line connecting "+
			    "the black Obelisk, the brown Obelisk, the blue Obelisk, "+
			    "the white Obelisk and the red Obelisk.";
			break;
		case 5:
			task_lines_drawn="There is a golden hue to the line connecting "+
			    "the black Obelisk, the brown Obelisk, the blue Obelisk, "+
			    "the white Obelisk and the red Obelisk.";
		default:
			task_lines_drawn="";
			break;
	}
}

void
set_task_objects_status(int value)
{
	task_objects_status = value;
	switch(task_objects_status)
	{
		case 2:
			task_objects_made="There is a small pile of dirt in the centre of the Obelisks.";
			break;
		case 3:
			task_objects_made="There is a small pile of wet dirt in the centre of the Obelisks.";
			break;
		case 4:
			task_objects_made="There is a small whirlwind swirling on top of a small pile of wet "+
			    "dirt in the centre of the Obelisks.";
			break;
		case 5:
			task_objects_made="There is a small fiery whirlwind swirling on top of a small pile of "+
			    "wet dirt in the centre of the Obelisks.";
			break;
		default:
		    task_objects_made="";
			break;
	}
}

public int
query_task_objects_status()
{
	return task_objects_status;
}

public string
query_task_objects_made()
{
	return task_objects_made;
}

public int
query_task_lines_status()
{
	return task_lines_status;
}

public string
query_task_lines_drawn()
{
	return task_lines_drawn;
}

int
do_smell(string str)
{
    if (!str)
    {
        write("You exhale deeply then breathe in a large breath "+
            "through your nose to take in the various smells around "+
            "you. It is almost overpowering, the mixture of all of "+
            "the different flowers and trees is intoxicating. You "+
            "almost pass out from the smell.\n");
        say(QCTNAME(TP)+" takes in a large breath through "+HIS+
            " nose and looks like "+HE+" is almost ready to pass out "+
            "from the intoxicating smell of the flowers and trees here.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'flowers' "))
    {
        NF("Which flowers would you like to smell? The pansy, "+
            "the iris, the hydrangea, the orchids, or the hanwi? "+
            "<smell pansy> <smell iris> <smell hydrangea> <smell orchid> "+
            "<smell hanwi>\n");
        return 0;
    }

    if (parse_command(str, TP, " [the] 'trees' "))
    {
        NF("Which trees would you like to smell? The pines, the "+
            "bonsai, or the gardenia? <smell pine> <smell bonsai> "+
            "<smell gardenia>\n");
        return 0;
    }

    if (parse_command(str, TP, " [the] 'pansy' "))
    {
        write("You bend over to smell the pansy. It smells faintly "+
            "sweet and slightly dusty.\n");
        say(QCTNAME(TP)+" bends over and smells a pansy.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'iris' "))
    {
        write("You bend over to smell the iris. It gives a soft, "+
            "pleasing scent.\n");
        say(QCTNAME(TP)+" bends over and smells an iris.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'hydrangea' "))
    {
        write("You bend over to smell the hydrangea. It has a "+
            "subdued honeyed scent.\n");
        say(QCTNAME(TP)+" bends over and smells a hydrangea.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'orchid' "))
    {
        write("You bend over to smell the orchid. It has a lavish, "+
            "musky odor.\n");
        say(QCTNAME(TP)+" bends over and smells an orchid.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'hanwi' "))
    {
        write("You bend over to smell the hanwi. It has a faint, "+
            "delicately spicy odor.\n");
        say(QCTNAME(TP)+" bends over and smells a hanwi.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'pine' [tree] "))
    {
        write("You bend over to smell the pine tree. It has a "+
            "heavy sharp scent.\n");
        say(QCTNAME(TP)+" bends over and smells a pine tree.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'bonsai' [tree] "))
    {
        write("You bend over to smell the bonsai tree. It smells "+
            "of the earth.\n");
        say(QCTNAME(TP)+" bends over and smells a bonsai tree.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'gardenia' [tree] "))
    {
        write("You bend over to smell the gardenia tree. It has a "+
            "strong but suprisingly delicate scent.\n");
        say(QCTNAME(TP)+" bends over and smells a gardenia tree.\n");
        return 1;
    }

    NF("What do you want to smell? The flowers? The trees?\n");
    return 0;
}

int
do_pick(string str)
{
    if (!str)
    {
        NF("Pick what?\n");
        return 0;
    }
    
    if (parse_command(str, TP, " [the] 'flower' "))
    {
        write("You dare not pick any of the flowers!\n");
        say(QCTNAME(TP)+" bends over to pick a flower, but decides against "+
            "it at the very last moment.\n");
        return 1;
    }

    if (parse_command(str, TP, " [the] 'flowers' "))
    {
        write("You dare not pick any of the flowers!\n");
        say(QCTNAME(TP)+" bends over to pick a flower, but decides against "+
            "it at the very last moment.\n");
        return 1;
    }

    if (parse_command(str, TP, " [my] 'nose' "))
    {
        write("Gross!\n");
        say(QCTNAME(TP)+" picks "+HIS+" nose.\n");
        TP->add_prop(LIVE_S_SOULEXTRA,("picking "+HIS+" nose"));
        return 1;
    }

    NF("Pick what?\n");
    return 0;
}

int
do_touch(string str)
{
    if (!str)
        return 0;

    if (parse_command(str, ({ }), " [the] 'obelisk' "))
    {
        write("Which obelisk would you like to touch? <touch black obelisk> "+
            "<touch white obelisk> <touch blue obelisk> <touch brown obelisk> "+
            "<touch red obelisk>\n");
        return 1;
    }

    if (parse_command(str, ({ }), " [the] 'black' 'obelisk' ") ||
    	parse_command(str, ({ }), " [the] 'first' 'obelisk' "))
    {
    	// Completed Guru quest AND is a Spirit Cleric
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT) && 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "life")
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the black obelisk. You feel the powers of Psuchae flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the black obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is a Master Cleric AND is a Spirit Cleric 
        if (GUILD_MANAGER->query_is_master_cleric(TP->query_real_name())&& 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "life")
        {
        	// They aren't in Elemental Form so they CAN'T enter
	        if (!present("_skiamorfi_object_",TP))
	        {
	            write("You reach your hand out and run it across the smoothness "+
	                "of the black obelisk. You feel the powers of Psuchae "+
	                "flowing throughout your body, the energy coursing through "+
	                "your veins. As you pull your hand away you feel as if "+
	                "hear a voice ringing in your mind yelling \"Help! Help "+
	                "me now! Become one with your element, quickly!\".\nYou "+
	                "quickly pull your hand away.\n");
	            say(QCTNAME(TP)+" runs "+HIS+" hand across the black obelisk "+
	                "briefly then quickly jerks it back to "+HIS+" side.\n");
	            return 1;
	        }
	        
	        // They are in Elemental Form so they CAN enter
	        write("You reach your shadowy hand out and run it across the "+
	            "smoothness of the black obelisk. Your body races with "+
	            "energy and you feel a presence within the obelisk. You "+
	            "hear a voice ringing in your mind yelling \"Help! Help "+
	            "me now!\". You look down to see that your hand has actually "+
	            "passed inside of the obelisk. You quickly pull your hand "+
	            "back and see that the shadowy hand is unharmed. You know "+
	            "in your mind that you could enter the obelisk if you "+
	            "wished to do so.\n");
	        say(QCTNAME(TP)+" runs "+HIS+" hand across the black obelisk "+
	            "briefly. Perhaps you are imagining it, but it appears "+
	            "as if "+HIS+" hand is actually passing through the surface "+
	            "of the obelisk itself. After a moment, "+HE+" pulls "+HIS+
	            " hand back from the obelisk.\n");
	        return 1;
	    }
        
        // Is a Spirit Cleric
        if (GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "life")
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the white obelisk. You feel the powers of Lady Aeria flowing "+
                "throughout your body, her energies coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the white obelisk "+
                "briefly.\n");
            return 1;
        }

        // Is not a Spirit Cleric
        write("You reach your hand out and run it across the smoothness of "+
            "the black obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the black obelisk "+
            "briefly.\n");
        return 1;
    }

    if (parse_command(str, ({ }), " [the] 'white' 'obelisk' ") ||
    	parse_command(str, ({ }), " [the] 'second' 'obelisk' "))
    {
    	// Completed Guru quest AND is a Air Cleric
    	if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT) && 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "air")
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the black obelisk. You feel the powers of Lady Aeria flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the white obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is a Master Cleric AND is an Air Cleric 
        if (GUILD_MANAGER->query_is_master_cleric(TP->query_real_name())&& 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "air")
        {
        	// They aren't in Elemental Form so they CAN'T enter
	        if (!present("_skiamorfi_object_",TP))
	        {
	            write("You reach your hand out and run it across the smoothness "+
	                "of the white obelisk. You feel the powers of Lady Aeria "+
	                "flowing throughout your body, the energy coursing through "+
	                "your veins. As you pull your hand away you feel as if "+
	                "hear a voice ringing in your mind yelling \"Help! Help "+
	                "me now! Become one with your element, quickly!\".\nYou "+
	                "quickly pull your hand away.\n");
	            say(QCTNAME(TP)+" runs "+HIS+" hand across the white obelisk "+
	                "briefly then quickly jerks it back to "+HIS+" side.\n");
	            return 1;
	        }
	        
	        // They are in Elemental Form so they CAN enter
	        write("You reach your airy hand out and run it across the "+
	            "smoothness of the white obelisk. Your body races with "+
	            "energy and you feel a presence within the obelisk. You "+
	            "hear a voice ringing in your mind yelling \"Help! Help "+
	            "me now!\". You look down to see that your hand has actually "+
	            "passed inside of the obelisk. You quickly pull your hand "+
	            "back and see that the airy hand is unharmed. You know "+
	            "in your mind that you could enter the obelisk if you "+
	            "wished to do so.\n");
	        say(QCTNAME(TP)+" runs "+HIS+" hand across the white obelisk "+
	            "briefly. Perhaps you are imagining it, but it appears "+
	            "as if "+HIS+" hand is actually passing through the surface "+
	            "of the obelisk itself. After a moment, "+HE+" pulls "+HIS+
	            " hand back from the obelisk.\n");
	        return 1;
	    }
	    
	    // Is an Air Cleric
        if (GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "life")
        {    
            write("You reach your hand out and run it across the smoothness of "+
                "the white obelisk. You feel the powers of Lady Aeria flowing "+
                "throughout your body, her energies coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the white obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is not an Air Cleric
        write("You reach your hand out and run it across the smoothness of "+
            "the white obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the white obelisk "+
            "briefly.\n");
        return 1;
    }

    if (parse_command(str, ({ }), " [the] 'blue' 'obelisk' ") ||
    	parse_command(str, ({ }), " [the] 'third' 'obelisk' "))
    {
    	if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT) && 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "water")
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the blue obelisk. You feel the powers of Lord Diabrecho flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the blue obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is a Master Cleric AND is an Water Cleric 
        if (GUILD_MANAGER->query_is_master_cleric(TP->query_real_name())&& 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "water")
        {
        	// They aren't in Elemental Form so they CAN'T enter
	        if (!present("_skiamorfi_object_",TP))
	        {
	            write("You reach your hand out and run it across the smoothness "+
	                "of the blue obelisk. You feel the powers of Lord Diabrecho "+
	                "flowing throughout your body, the energy coursing through "+
	                "your veins. As you pull your hand away you feel as if "+
	                "hear a voice ringing in your mind yelling \"Help! Help "+
	                "me now! Become one with your element, quickly!\".\nYou "+
	                "quickly pull your hand away.\n");
	            say(QCTNAME(TP)+" runs "+HIS+" hand across the blue obelisk "+
	                "briefly then quickly jerks it back to "+HIS+" side.\n");
	            return 1;
	        }
	        
	        // They are in Elemental Form so they CAN enter
	        write("You reach your watery hand out and run it across the "+
	            "smoothness of the blue obelisk. Your body races with "+
	            "energy and you feel a presence within the obelisk. You "+
	            "hear a voice ringing in your mind yelling \"Help! Help "+
	            "me now!\". You look down to see that your hand has actually "+
	            "passed inside of the obelisk. You quickly pull your hand "+
	            "back and see that the watery hand is unharmed. You know "+
	            "in your mind that you could enter the obelisk if you "+
	            "wished to do so.\n");
	        say(QCTNAME(TP)+" runs "+HIS+" hand across the blue obelisk "+
	            "briefly. Perhaps you are imagining it, but it appears "+
	            "as if "+HIS+" hand is actually passing through the surface "+
	            "of the obelisk itself. After a moment, "+HE+" pulls "+HIS+
	            " hand back from the obelisk.\n");
	        return 1;
	    }
        
        // Is a Water Cleric	
        if (GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "water")
        {
            write("You reach your hand out and run it across the smoothness "+
                "of the blue obelisk. You feel the powers of Lord Diabrecho "+
                "flowing throughout your body, his energies coursing through "+
                "your veins. As you pull your hand away, the feeling "+
                "subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the blue obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is not a Water Cleric
        write("You reach your hand out and run it across the smoothness of "+
            "the blue obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the blue obelisk "+
            "briefly.\n");
        return 1;
    }

    if (parse_command(str, ({ }), " [the] 'brown' 'obelisk' ") ||
    	parse_command(str, ({ }), " [the] 'fourth' 'obelisk' "))
    {
    	if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT) && 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "earth")
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the brown obelisk. You feel the powers of Lady Gu flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the brown obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is a Master Cleric AND is an Earth Cleric 
        if (GUILD_MANAGER->query_is_master_cleric(TP->query_real_name())&& 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "earth")
        {
        	// They aren't in Elemental Form so they CAN'T enter
	        if (!present("_skiamorfi_object_",TP))
	        {
	            write("You reach your hand out and run it across the smoothness "+
	                "of the brown obelisk. You feel the powers of Lady Gu "+
	                "flowing throughout your body, the energy coursing through "+
	                "your veins. As you pull your hand away you feel as if "+
	                "your very soul is being pulled into the obelisk. You "+
	                "hear a voice ringing in your mind yelling \"Help! Help "+
	                "me now! Become one with your element, quickly!\".\nYou "+
	                "quickly pull your hand away.\n");
	            say(QCTNAME(TP)+" runs "+HIS+" hand across the brown obelisk "+
	                "briefly then quickly jerks it back to "+HIS+" side.\n");
	            return 1;
	        }
	        
	        // They are in Elemental Form so they CAN enter
	        write("You reach your rocky hand out and run it across the "+
	            "smoothness of the brown obelisk. Your body races with "+
	            "energy and you feel a presence within the obelisk. You "+
	            "hear a voice ringing in your mind yelling \"Help! Help "+
	            "me now!\". You look down to see that your hand has actually "+
	            "passed inside of the obelisk. You quickly pull your hand "+
	            "back and see that the rocky hand is unharmed. You know "+
	            "in your mind that you could enter the obelisk if you "+
	            "wished to do so.\n");
	        say(QCTNAME(TP)+" runs "+HIS+" hand across the brown obelisk "+
	            "briefly. Perhaps you are imagining it, but it appears "+
	            "as if "+HIS+" hand is actually passing through the surface "+
	            "of the obelisk itself. After a moment, "+HE+" pulls "+HIS+
	            " hand back from the obelisk.\n");
	        return 1;
	    }
        
        // Is an Earth Cleric	
        if (GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "earth")
        {
            write("You reach your hand out and run it across the smoothness "+
                "of the brown obelisk. You feel the powers of Lady Gu "+
                "flowing throughout your body, her energies coursing through "+
                "your veins. As you pull your hand away, the feeling "+
                "subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the brown obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is not an Earth Cleric
        write("You reach your hand out and run it across the smoothness of "+
            "the brown obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the brown obelisk "+
            "briefly.\n");
        return 1;
    }

    if (parse_command(str, ({ }), " [the] 'red' 'obelisk' ") ||
    	parse_command(str, ({ }), " [the] 'fifth' 'obelisk' "))
    {
    	if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT) && 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "fire")
        {
            write("You reach your hand out and run it across the smoothness of "+
                "the red obelisk. You feel the powers of Lord Pyros flowing "+
                "throughout your body, the energy coursing through your veins. "+
                "As you pull your hand away, the feeling subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the red obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is a Master Cleric AND is a Fire Cleric 
        if (GUILD_MANAGER->query_is_master_cleric(TP->query_real_name())&& 
        	GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "fire")
        {
        	// They aren't in Elemental Form so they CAN'T enter
	        if (!present("_skiamorfi_object_",TP))
	        {
	            write("You reach your hand out and run it across the smoothness "+
	                "of the red obelisk. You feel the powers of Lord Pyros "+
	                "flowing throughout your body, the energy coursing through "+
	                "your veins. As you pull your hand away you feel as if "+
	                "your very soul is being pulled into the obelisk. You "+
	                "hear a voice ringing in your mind yelling \"Help! Help "+
	                "me now! Become one with your element, quickly!\".\nYou "+
	                "quickly pull your hand away.\n");
	            say(QCTNAME(TP)+" runs "+HIS+" hand across the red obelisk "+
	                "briefly then quickly jerks it back to "+HIS+" side.\n");
	            return 1;
	        }
	        
	        // They are in Elemental Form so they CAN enter
	        write("You reach your fiery hand out and run it across the "+
	            "smoothness of the red obelisk. Your body races with "+
	            "energy and you feel a presence within the obelisk. You "+
	            "hear a voice ringing in your mind yelling \"Help! Help "+
	            "me now!\". You look down to see that your hand has actually "+
	            "passed inside of the obelisk. You quickly pull your hand "+
	            "back and see that the fiery hand is unharmed. You know "+
	            "in your mind that you could enter the obelisk if you "+
	            "wished to do so.\n");
	        say(QCTNAME(TP)+" runs "+HIS+" hand across the red obelisk "+
	            "briefly. Perhaps you are imagining it, but it appears "+
	            "as if "+HIS+" hand is actually passing through the surface "+
	            "of the obelisk itself. After a moment, "+HE+" pulls "+HIS+
	            " hand back from the obelisk.\n");
	        return 1;
	    }
        
        // Is a fire Cleric
        if (GUILD_MANAGER->query_primary_element(TP->query_real_name()) == "fire")
        {
            write("You reach your hand out and run it across the smoothness "+
                "of the red obelisk. You feel the powers of Lord Pyros "+
                "flowing throughout your body, his energies coursing through "+
                "your veins. As you pull your hand away, the feeling "+
                "subsides.\n");
            say(QCTNAME(TP)+" runs "+HIS+" hands across the red obelisk "+
                "briefly.\n");
            return 1;
        }
        
        // Is not a Fire Cleric
        write("You reach your hand out and run it across the smoothness of "+
            "the red obelisk briefly.\n");
        say(QCTNAME(TP)+" runs "+HIS+" hands across the red obelisk "+
            "briefly.\n");
        return 1;
    }
    
    write("Which obelisk would you like to touch? <touch black obelisk> "+
        "<touch white obelisk> <touch blue obelisk> <touch brown obelisk> "+
        "<touch red obelisk>\n");
    return 1;
}

string
query_task_progress_message()
{
	string progress_message;
	object task_object = present(EC_CHILD_MANDALA_TASK,TP);
	if (task_object->query_task_status() > 5)
	{
		progress_message="The voice of Psuchae fills your mind and says:\n"+
	    "You have completed this portion of the task already.\n";
	    return progress_message;
	}
	
	TO->set_task_lines_status(task_object->query_task_status());
	TO->set_task_objects_status(task_object->query_task_status());
	TO->update_long_desc();
	tell_room(TO,"The black lines flash with a golden hue for a "+
	    "moment.\n");
	progress_message="The voice of Psuchae fills your mind and says:\n"+
	    "I have reset your progress in your task. You may "+
	    "see your current progress by examining the black "+
	    "lines to see where the light has ended. ";
	switch(task_object->query_task_status())
	{
		case 1:
			progress_message += "To activate Lady Gu, you will "+
	    		"need to rub some dirt from the ground on her Obelisk.\n";
			break;
		case 2:
			progress_message += "\nThe voice of Lady Gu fills "+
			    "your mind and says:\nTo activate Lord Diabrecho, you "+
			    "will need to pour some water on his Obelisk.\n";
			tell_room(TO,"A small pile of dirt forms in the "+
	    		"centre of the Obelisks.\n"); 
			break;
		case 3:
			progress_message += "\nThe voice of Lord Diabrecho fills "+
			    "your mind and says:\nTo activate Lady Aeria, you "+
			    "will need to breathe on her Obelisk.\n";
			tell_room(TO,"A small pile of wet dirt forms in the "+
	    		"centre of the Obelisks.\n"); 
			break;
		case 4:
			progress_message += "\nThe voice of Lady Aeria fills "+
			    "your mind and says:\nTo activate Lord Pyros, you "+
			    "will need to ignite his Obelisk with fire.\n";
			tell_room(TO,"A small tornado forms above a pile of "+
			    "wet dirt forms in the centre of the Obelisks.\n"); 
			break;
		case 5:
			progress_message += "\nThe voice of Lord Pyros fills "+
			    "your mind and says:\nTo activate the powers of "+
			    "Psuchae, you will need to stab your hand with "+
			    "a Cermonial Dagger and drip some of your blood "+
			    "into the fiery whirlwind in the centre of the "+
			    "Obelisks.\n";
			tell_room(TO,"A small fiery tornado forms above a pile "+
			    "of wet dirt forms in the centre of the Obelisks.\n");
			break;
	    default:
	    	progress_message += "\n";
	    	break;
	}
    
	return progress_message;
}

int
do_pray(string str)
{
	object task_object;
	string task_progress_message;
	
	task_object = present(EC_CHILD_MANDALA_TASK,TP);
	
	if (!task_object)
		return 0;
		
	if (!str)
	{
		NF("Pray to what?\n");
		return 0;
	}
	
	if (!(parse_command(str, ({}),"[to] [the] 'Five'")))
	{
		NF("Pray to what, the Five?\n");
		return 0;
	}
	
	if (task_object->query_task_status() != 0)
	{
		task_progress_message = TO->query_task_progress_message();
		NF(task_progress_message);	
		return 0;
	}
	
	string *mandala_task_one_pmessages = ({"You stand in the middle "+
		"of the Obelisks, close your eyes and pray to the Five.\n\n",
		"The black Obelisk pulses light for a brief moment.\n\n",
		
	    "You hear a gentle voice in your mind say:\n"+
	    "Greetings, "+TP->query_name()+". I am Psuchae and on "+
	    "behalf of the Elementals, let me be the first to welcome "+
	    "you officially into the Circle. You have been tasked to "+
	    "seek out your Sporos.\n\n",
	    
	    "The Sporos is the seed or heart of your Sacred Mandala. "+
	    "Each Sporos is unique in that a portion of its creator's "+
	    "soul is infused within it.\n\n",
	    
	    "In order for you to gain such a thing, you will have to "+
	    "awaken all of the Elementals in their Obelisks. Allow me "+
	    "to point you in the right direction for your first awakening.\n\n",
	    
	    "A shimmering golden light forms at the bottom of the black "+
	    "Obelisk. After a few seconds, the light travels down the "+
	    "black line from the black Obelisk to the brown Obelisk, "+
	    "lighting it up in a golden hue as it does so.\n\n",
	    
	    "The voice of Psuchae fills your mind again and says:\n"+
	    "To activate Lady Gu, you will need to rub some dirt from "+
	    "the ground on her Obelisk.\n"+
	    "Should you ever forget what you are doing, simply pray "+
		"to the Five again and I shall re-light your path.\n\n"});
		
	string *mandala_task_one_vmessages = ({"",
	    "The black Obelisk pulses light for a brief moment.\n\n",
		"",
		"",
		"",
		"A shimmering golden light forms at the bottom of the black "+
	    "Obelisk. After a few seconds, the light travels down the "+
	    "black line from the black Obelisk to the brown Obelisk, "+
	    "lighting it up in a golden hue as it does so.\n",
		""});
	
	for (int i=0; i < sizeof(mandala_task_one_pmessages); i++)
	{
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, mandala_task_one_pmessages[i]));
		set_alarm((10.0*itof(i)), 0.0, &tell_room(environment(TP), mandala_task_one_vmessages[i],({TP})));
		
	}    
	
	task_object->set_task_status(1);
	TO->set_task_lines_status(1);
	TO->update_long_desc();
	return 1;
}

int
do_rub(string str)
{
	object task_object;
	string task_progress_message;
	
	task_object = present(EC_CHILD_MANDALA_TASK,TP);
	
	if (!task_object)
		return 0;
		
	if (!str)
	{
		NF("Rub what?\n");
		return 0;
	}
	
	if (!(parse_command(str, ({}),"'dirt' [on] [the] [Gu] [gu] [fourth] [4th] 'obelisk'")))
	{
		NF("Rub what on what? Did you mean dirt on the Gu obelisk?\n");
		return 0;
	}
	
	if (task_object->query_task_status() != 1)
	{
		task_progress_message = TO->query_task_progress_message();
		NF(task_progress_message);	
		return 0;
	}		
	
	string *mandala_task_two_pmessages = ({"You stand in the front of the "+
		"brown Obelisk. Reaching down in front of you, you grab a small "+
		"handful of dirt and rub it onto the Obelisk. The dirt is amazingly "+
		"absorbed by the Obelisk and it vibrates briefly.\n\n",
		"You hear a powerful voice in your mind say:\n"+
	    "Greetings, "+TP->query_name()+". I am Lady Gu. Thank you for "+
	    "awakening me in the Obelisk. I shall begin the process for "+
	    "you to get your Sporos.\n\n",
	    "A small pile of dirt forms in the centre of the Obelisks.\n\n",
	    "The voice of Lady Gu fills your mind again and says:\nAllow me "+
	    "to point you in the direction of your next awakening.\n\n",
	    "A shimmering golden light forms at the bottom of the brown "+
	    "Obelisk. After a few seconds, the light travels down the black "+
	    "line from the brown Obelisk to the blue Obelisk, lighting it up in a "+
	    "golden hue as it does so.\n\n",
	    "The voice of Lady Gu fills your mind once more and says:\n"+
	    "To activate Lord Diabrecho, you will need to pour some water "+
		"on his Obelisk.\n\n"});	
		
	string *mandala_task_two_vmessages = ({QCTNAME(TP)+" reaches down in "+
		"front of "+HIM+"self, grabbing a handful of dirt as "+HE+" does "+
		"so. "+capitalize(HE)+" rubs the dirt on the brown Obelisk, which "+
		"seems to absorb it.\n\n",
		"",
	    "A small pile of dirt forms in the centre of the Obelisks.\n\n",
	    "",
	    "A shimmering golden light forms at the bottom of the brown "+
	    "Obelisk. After a few seconds, the light travels down the black "+
	    "line from the brown Obelisk to the blue Obelisk, lighting it up in a "+
	    "golden hue as it does so.\n\n",
	    ""});
	
	for (int i=0; i < sizeof(mandala_task_two_pmessages); i++)
	{
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, mandala_task_two_pmessages[i]));
		set_alarm((10.0*itof(i)), 0.0, &tell_room(environment(TP), mandala_task_two_vmessages[i],({TP})));
		
	} 
	
	task_object->set_task_status(2);
	TO->set_task_lines_status(task_object->query_task_status());
	TO->set_task_objects_status(task_object->query_task_status());
	TO->update_long_desc();
	return 1;
}

int
do_pour(string str)
{
	object task_object;
	string task_progress_message;
	
	task_object = present(EC_CHILD_MANDALA_TASK,TP);
	
	if (!task_object)
		return 0;
		
	if (!str)
	{
		NF("Pour what on what?\n");
		return 0;
	}
	
	if (!(parse_command(str, ({}),"'water' [on] [the] [Diabrecho] [diabrecho] [third] [3rd] 'obelisk'")))
	{
		NF("Pour what on what? Did you mean water on the Diabrecho obelisk?\n");
		return 0;
	}
	
	if (!present("water",TP))
	{
		NF("You can't pour water on the obelisk without having any water.\n");
		return 0;
	}
	
	if (task_object->query_task_status() != 2)
	{
		task_progress_message = TO->query_task_progress_message();
		NF(task_progress_message);	
		return 0;
	}
	
	string *mandala_task_three_pmessages = ({"You stand in the front of "+
		"the blue Obelisk. You pour some water onto the Obelisk. The water "+
		"is amazingly absorbed by the Obelisk and it vibrates briefly.\n\n",
		"You hear a powerful voice in your mind say:\n"+
	    "Greetings, "+TP->query_name()+". I am Lord Diabrecho. Thank you for "+
	    "awakening me in the Obelisk. I shall continue the process for "+
	    "you to get your Sporos.\n\n",
	    "The small pile of dirt in the centre of the Obelisks becomes wet.\n\n",
	    "The voice of Lord Diabrecho fills your mind again and says:\n"+
	    "Allow me to point you in the direction of your next awakening.\n\n",
	    "A shimmering golden light forms at the bottom of the blue Obelisk. "+
	    "After a few seconds, the light travels down the black line from the "+
	    "blue Obelisk to the white Obelisk, lighting it up in a "+
	    "golden hue as it does so.\n\n",
	    "The voice of Lord Diabrecho fills your mind once more and says:\n"+
		"To activate Lady Aeria, you will need to breathe on her Obelisk.\n\n"});
	
	string *mandala_task_three_vmessages = ({QCTNAME(TP)+" pours some water "+
		"onto the blue Obelisk, which seems to absorb it as "+HE+" does so.\n\n",
		"",
	    "The small pile of dirt in the centre of the Obelisks becomes wet.\n\n",
	    "",
	    "A shimmering golden light forms at the bottom of the blue Obelisk. "+
	    "After a few seconds, the light travels down the black line from the "+
	    "blue Obelisk to the white Obelisk, lighting it up in a "+
	    "golden hue as it does so.\n\n",
	    ""});
			
	for (int i=0; i < sizeof(mandala_task_three_pmessages); i++)
	{
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, mandala_task_three_pmessages[i]));
		set_alarm((10.0*itof(i)), 0.0, &tell_room(environment(TP), mandala_task_three_vmessages[i],({TP})));
		
	}
	
	task_object->set_task_status(3);
	TO->set_task_lines_status(task_object->query_task_status());
	TO->set_task_objects_status(task_object->query_task_status());
	TO->update_long_desc();
	return 1;
}

int
do_breathe(string str)
{
	object task_object;
	string task_progress_message;
	
	task_object = present(EC_CHILD_MANDALA_TASK,TP);
	
	if (!task_object)
		return 0;
		
	if (!str)
		return 0;
		
	if (!(parse_command(str, ({}),"[on] [the] [white] [aeria] [Aeria] [second] [2nd] 'obelisk'")))
	{
		NF("Breathe on what? Did you mean breathe on the Aeria obelisk?\n");
		return 0;
	}
	
	if (task_object->query_task_status() != 3)
	{
		task_progress_message = TO->query_task_progress_message();
		NF(task_progress_message);	
		return 0;
	}
	
	string *mandala_task_four_pmessages = ({"You stand in the front of the "+
		"white Obelisk. You inhale and then breathe gently onto the Obelisk. "+
		"The Obelisk vibrates briefly.\n\n",
		"You hear a gentle voice in your mind say:\n"+
	    "Greetings, "+TP->query_name()+". I am Lady Aeria. Thank you for "+
	    "awakening me in the Obelisk. I shall continue the process for "+
	    "you to get your Sporos.\n\n",
	    "A small whirlwind forms above the pile of wet dirt in the centre "+
	    "of the Obelisks.\n\n",
	    "The voice of Lady Aeria fills your mind again and says:\n"+
	    "Allow me to point you in the direction of your next awakening.\n\n",
	    "A shimmering golden light forms at the bottom of the white Obelisk. "+
	    "After a few seconds, the light travels down the black line from the "+
	    "white Obelisk to the red Obelisk, lighting it up in a "+
	    "golden hue as it does so.\n\n",
	    "The voice of Lady Aeria fills your mind once more and says:\n"+
		"To activate Lord Pyros, you will need to ignite his Obelisk with fire.\n\n"});
		
	string *mandala_task_four_vmessages = ({QCTNAME(TP)+" stands in front of "+
		"the white Obelisk, inhales and then gently breathes on it.\n\n",
		"",
		"A small whirlwind forms above the pile of wet dirt in the centre of the "+
		"Obelisks.\n\n",
		"",
		"A shimmering golden light forms at the bottom of the white Obelisk. "+
		"After a few seconds, the light travels down the black line from the "+
		"white Obelisk to the red Obelisk, lighting it up in a golden hue as "+
		"it does so.\n\n",
		""});
	
	for (int i=0; i < sizeof(mandala_task_four_pmessages); i++)
	{
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, mandala_task_four_pmessages[i]));
		set_alarm((10.0*itof(i)), 0.0, &tell_room(environment(TP), mandala_task_four_vmessages[i],({TP})));
		
	}
	
	task_object->set_task_status(4);
	TO->set_task_lines_status(task_object->query_task_status());
	TO->set_task_objects_status(task_object->query_task_status());
	TO->update_long_desc();
	
	return 1;
}

int
do_ignite(string str)
{
	object task_object, torch;
	string task_progress_message;
	
	task_object = present(EC_CHILD_MANDALA_TASK,TP);
	
	if (!task_object)
		return 0;
		
	if (!str)
	{
		NF("Ignite what?\n");
		return 0;
	}
	
	if (!(parse_command(str, ({}),"[the] [red] [pyros] [Pyros] [fifth] [5th] 'obelisk' [with] [a] [the] 'torch'")))
	{
		NF("Ignite what with what? Did you mean ignite the Pyros obelisk with a torch?\n");
		return 0;
	}
	
	torch = (present("torch",TP));
	if (!torch)
	{
		NF("You can't ignite anything without a burning torch.\n");
		return 0;
	}
	
	if (torch->query_lit() != -1)
	{
		NF("You can't ignite anything without a burning torch.\n");
		return 0;
	}
		
	if (task_object->query_task_status() != 4)
	{
		task_progress_message = TO->query_task_progress_message();
		NF(task_progress_message);	
		return 0;
	}
	
	string *mandala_task_five_pmessages = ({"You stand in the front of the "+
		"red Obelisk. You touch the flame to the Obelisk and it vibrates "+
		"briefly.\n\n",
		"You hear a powerful voice in your mind say:\n"+
	    "Greetings, "+TP->query_name()+". I am Lord Pyros. Thank you for "+
	    "awakening me in the Obelisk. I shall continue the process for "+
	    "you to get your Sporos.\n\n",
	    "Flames begin to swirl inside the small whirlwind above the pile "+
	    "of wet dirt in the centre of the Obelisks.\n\n",
	    "The voice of Lord Pyros fills your mind again and says:\n"+
	    "Allow me to point you in the direction of your next awakening.\n\n",
	    "A shimmering golden light forms at the bottom of the red Obelisk. "+
	    "After a few seconds, the light travels down the black line from the "+
	    "red Obelisk to the black Obelisk, lighting it up in a golden hue as "+
	    "it does so.\n\n",
	    "The voice of Lord Pyros fills your mind once more and says:\n"+
	    "To activate the powers of Psuchae, you will need to stab your hand "+
	    "with a Ceremonial Dagger and pour some of your blood into the fiery "+
		"whirlwind in the centre of the Obelisks.\n\n"});
		
	string *mandala_task_five_vmessages = ({QCTNAME(TP)+" stands in front of "+
		"the red Obelisk and touches a flame to it.\n\n",
		"",
		"Flames begin to swirl inside the small whirlwind above the pile of "+
		"wet dirt in the centre of the Obelisks.\n\n",
		"",
	    "A shimmering golden light forms at the bottom of the red Obelisk. "+
	    "After a few seconds, the light travels down the black line from the "+
	    "red Obelisk to the black Obelisk, lighting it up in a golden hue as "+
	    "it does so.\n\n",
		""});
	
	for (int i=0; i < sizeof(mandala_task_five_pmessages); i++)
	{
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, mandala_task_five_pmessages[i]));
		set_alarm((10.0*itof(i)), 0.0, &tell_room(environment(TP), mandala_task_five_vmessages[i],({TP})));
		
	}
	
	task_object->set_task_status(5);
	TO->set_task_lines_status(task_object->query_task_status());
	TO->set_task_objects_status(task_object->query_task_status());
	TO->update_long_desc();
	
	return 1;
}

int
do_stab(string str)
{
	object task_object, dagger;
	string task_progress_message;
	
	task_object = present(EC_CHILD_MANDALA_TASK,TP);
	
	if (!task_object)
		return 0;
		
	if (!str)
	{
		NF("Stab what with what?\n");
		return 0;
	}
	
	if (!(parse_command(str, ({}),"[my] [myself] 'hand' [with] [a] [the] [cermonial] 'dagger'")))
	{
		NF("Stab what? Did you mean your hand with the ceremonial dagger?\n");
		return 0;
	}
	
	dagger = (present("_spirit_ceremonial_dagger_",TP));
	if (!dagger)
	{
		NF("You can't stab your hand without the ceremonial dagger.\n");
		return 0;
	}	
	
	if (task_object->query_task_status() != 5)
	{
		task_progress_message = TO->query_task_progress_message();
		NF(task_progress_message);	
		return 0;
	}
	
	string *mandala_task_six_pmessages = ({"You stand in the front of the "+
		"fiery whirlwind in the center of the Obelisks. You gently and "+
		"shallowly stab the Ceremonial Dagger into your hand, just enough "+
		"to get a small pool of blood in your palm.\n\n",
		"You close your hand and reach your blood filled "+
	    "palm above the fiery whirlwind and let the blood drip right into "+
	    "the centre of it.\n\n",
	    "The flames seem to grow stronger and the winds "+
	    "of the whirlwind spin faster as it consumes the blood.\n\n",
	    "The whirlwind digs its way down into the wet dirt pile below it, "+
	    "shrinking in size the further down it burrows. Just as the last "+
	    "bit of the whirlwind descends into the wet dirt, the dirt itself "+
	    "closes over the hole the whirlwind has created.\n\n",
	    "The wet dirt then appears to be being absorbed "+
	    "by the ground itself until only a very small patch of it remains.\n\n",
	    "All is calm for a few moments and then a small vine begins to poke its "+
	    "way out of the soil, growing upwards very quickly. Once it reaches "+
	    "about half a metre high, it begins to curve back towards the ground and "+
	    "then stops growing.\n\n",
	    "At the very end of the vine, a pod starts to grow, causing the vine to "+
	    "bend even further towards the ground. As the pod gets larger, the vine "+
	    "bends more and more until it is almost allowing the pod to touch the "+
	    "ground.\n\n",
	    "Instinctively you cup your hands together underneath the pod. As it "+
	    "touches the remnants of blood in your palm, "+
	    "it detaches itself from the vine, falling into your palm.\n\n",
	    "The vine retreats back into the soil, the dirt closes up over top of "+
	    "where it was, leaving no trace it was ever there.\n\n",
	    "A shimmering golden light forms at the bottom of the black Obelisk. "+
	    "After a few seconds, the light travels down all of the black lines, "+
	    "removing the golden hue behind it as it does so. Once the light hits the "+
	    "black Obelisk again, it flashes brightly then disappears.\n\n",
	    "The voice of Psuchae fills your mind once more and says:\n"+
	    "You now have the inital seed of your Sporos. You will need "+
	    "to take that back to Brother Jardeth to have it extracted. He will "+
		"know what to do next.\n\n"});
	string *mandala_task_six_vmessages = ({QCTNAME(TP)+" stands in front of "+
		"the fiery whirlwind in the center of the Obelisks. "+capitalize(HE)+
		" gently and shallowly stabs a dagger into "+HIS+" hand, just enough "+
		"to get a small pool of blood in "+HIS+" palm.\n\n",
		capitalize(HE)+" closes "+HIS+" hand and reaches "+
	    HIS+" blood filled palm above the fiery whirlwind and lets the blood "+
	    "drip right into the centre of it.\n\n",
	    "The flames seem to grow stronger and the winds of the whirlwind spin "+
	    "faster as it consumes the blood.\n\n",
	    "The whirlwind digs its way down into the wet dirt pile below it, "+
	    "shrinking in size the further down it burrows. Just as the last bit "+
	    "of the whirlwind descends into the wet dirt, the dirt itself closes "+
	    "over the hole the whirlwind has created.\n\n",
	    "The wet dirt then appears to be absorbed by the ground itself "+
	    "until only a very small patch of it remains.\n\n",
	    "All is calm for a few moments and then a small "+
	    "vine begins to poke its way out of the soil, growing upwards very "+
	    "quickly. Once it reaches about half a metre high, it begins to curve "+
	    "back towards the ground and then stops growing.\n\n",
	    "At the very end of the vine, a pod starts to grow, causing the vine "+
	    "to bend even further towards the ground. As the pod gets larger, "+
	    "the vine bends more and more until it is almost allowing the pod to "+
	    "touch the ground.\n\n",
	    QCTNAME(TP)+" cups "+HIS+" hands together underneath the pod. As it "+
	    "touches the remnants of blood in "+HIS+" palm, it detaches itself "+
	    "from the vine, falling into "+HIS+" palm.\n\n",
	    "The vine retreats back into the soil, the dirt closes up over top "+
	    "of where it was, leaving no trace it was ever there.\n\n",
	    "A shimmering golden light forms at the bottom of the black Obelisk. "+
	    "After a few seconds, the light travels down all of the black lines, "+
	    "removing the golden hue behind it as it does so. Once the light hits the "+
	    "black Obelisk again, it flashes brightly then disappears.\n\n",
		""});
	
	for (int i=0; i < sizeof(mandala_task_six_pmessages); i++)
	{
		set_alarm((10.0*itof(i)), 0.0, &tell_object(TP, mandala_task_six_pmessages[i]));
		set_alarm((10.0*itof(i)), 0.0, &tell_room(environment(TP), mandala_task_six_vmessages[i],({TP})));
		
	}
	
	task_object->set_task_status(6);
	TO->set_task_lines_status(task_object->query_task_status());
	TO->set_task_objects_status(task_object->query_task_status());
	object sporos_pod = clone_object(ELEMENTALIST_OBJS+"sporos_pod");
	sporos_pod->move(TP,1);
	TO->update_long_desc();
	
	return 1;
}

int
do_enter(string str)
{
	if (!str)
	{
		NF("Enter what?\n");
		return 0;
	}

    if (!IS_MEMBER(TP))
    {
        NF("What?\n");
        return 0;
    }
    
    if (present("_elemental_child_mandala",TP))
    {
    	write("You cannot enter the obelisk until you have "+
    	    "carved the Word of Power on your Sacred Manadala!\n");
    	return 1;
    }
    
    if (str != "obelisk")
    {
        NF("Enter what?\n");
        return 0;
    }

    if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    {
        write("You cannot seem to enter the obelisk anymore.\n");
        return 1;
    }

    if (!present("_skiamorfi_object_",TP))
    {
        write("You boldy step forth and solidly walk into an "+
            "obelisk, your body falling to the ground with a "+
            "loud 'thud' sound. You feel a bit dizzy and very "+
            "embarrased.\n");
        say(QCTNAME(TP)+" boldy steps forward and walks right an "+
            "the obelisk, "+HIS+" body falling backwards to the "+
            "ground with a loud 'thud' sound. "+capitalize(HE)+" stands "+
            "up, looking a little dizzy and quite embarrased.\n");
        TP->command("blush");
        return 1;
    }
    
    if (TP->query_stat(SS_OCCUP) < 140)
    {
    	write("You hear a voice echo in your mind saying: "+
    	    "'You are not yet ready to enter. Come back when you have "+
    	    "grown a bit more.'\n");
        return 1;
    }    

    write("You boldy step forth and walk right though the side of the "+
        "obelisk. You suddenly find yourself elsewhere.\n");
    say(QCTNAME(TP)+" boldy steps foward and walks right through the side "+
        "of an obelisk, disappearing from your sight.\n");
    TP->move_living("X",ELEMENTALIST_TEMPLE+"obelisk_entrance");
    tell_room(environment(TP),QCTNAME(TP)+" arrives from outside of the "+
        "obelisk.\n",TP);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_smell,"smell");
    add_action(do_pick,"pick");
    add_action(do_touch,"touch");
    add_action(do_pray,"pray");
    add_action(do_rub,"rub");
    add_action(do_pour,"pour");
    add_action(do_breathe,"breathe");
    add_action(do_ignite,"ignite");
    add_action(do_stab,"stab");
    add_action(do_stab,"drip");
    add_action(do_enter,"enter");
}
                                                      
