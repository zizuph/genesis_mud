/*                                                                        *
 *  file name:   ~soap.c                                                  *
 *  creator(s):  Zielia                                                   *
 *  last update:                                                          *
 *  purpose:     Object mortals can buy which they can use to remove      *
 *  various sublocs from their description.                               *
 *  note:                                                                 *
 *  bug(s):                                                               *
 *  to-do:                                                                */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Avenir/include/deities.h"
#include "zigg.h"

inherit "/std/object";
inherit "/lib/keep";

#define US_PURITY     139058
//#define VAR_ADJS ({ "fancy", "small", adj, color, shape +"-shaped", })

private static string adj   =   one_of_list(({ "pale", "light", "marbleized",
    "speckled"}));

private static string color =   one_of_list(({ "blue", "pink", "yellow", "green",
    "orange", "green", "purple", }));

private static string shape =   one_of_list(({ "deer", "aglyna", "bird",
    "newt", "bicorn", "cat", "monkey", "fairy",
    "oval", "rectangle", }));

private static string smell =   one_of_list(({ "fresh and clean",
    "like a sea breeze", "like fresh linen",
    "like a clean wind", "faintly floral",
    "like you are standing near a waterfall",
  }));

private static string emblem =  one_of_list(({ "an octagon", "a lock and key",
    "a quill pen", "a flame", "a crescent",
    "a circle with a bolt of lightning dividing it",
    "a hammer", "a coin", "a cross and circle",
    "two circles half-merged", "a knife", "an orb",
    "a teardrop", "a closed fist", "a loaf of bread",
    "a wavy line", "a spiral", "a triangle pointing up",
    "a wand with serpents wrapped around it in a helix",
    "a cradle", "a flute", "a grinning skull",
    "a triangle pointing down",  }));

private static int wear, uses, max_uses;

private int
f_dissolve(void)
{
    string embossing;
    int val = 100;

    if (uses < max_uses)
    {
	float max, cur;

	cur = itof(uses);
	max = itof(max_uses);
	val = ftoi(100.0 - (((max - cur) / max) * 100.0));
    }

    if (val > 70)
    {
	if (wear <= 0)
	{
	    if( shape == "rectangle" || shape == "oval" )
	    {
		embossing = " with an emblem of "+ emblem +
		" embossed on the front";
	    }
	    else
	    {
		embossing = "";
	    }
	    set_short(adj +" "+ color +" "+ shape +"-shaped soap");
	    set_adj(({ "fancy", "small", adj, color, shape +"-shaped",
	    	"sybarun", "ziggurat"}));
	    set_long("It is a small fancy soap that can be used to wash "+
	      "the face and body. It is "+ adj +" "+ color +" and molded "+
	      "into the shape of "+ LANG_ADDART(shape) +". The lines and "+
	      "edges are sharp and well-defined"+ embossing +". The soap "+
	      "has a fresh scent and would probably help you feel nice and "+
	      "clean. Try <help soap> to learn more.\n");

	    wear = 1;
	}
	return 1;
    }
    else if (val > 40)
    {
	if (wear == 1)
	{
	    if( shape == "rectangle" || shape == "oval" )
	    {
		embossing = ", and there is a faint, slightly raised "+
		"emblem of "+ emblem +" on the front";
	    }
	    else
	    {
		embossing = "";
	    }

	    set_long("It is a small fancy soap that can be used to wash "+
	      "the face and body. It is "+ adj +" "+ color +" and resembles "+
	      LANG_ADDART(shape) +". The lines and edges are worn and "+
	      "rounded from use"+ embossing +". The soap has a fresh scent "+
	      "and would probably help you feel nice and clean.\n "+
	      " Try <help soap> to learn more.\n");

	    wear = 2;;
	}

	return 1;
    }
    else if (val > 10)
    {
	if (wear == 2)
	{
	    set_short("rather worn "+ adj +" "+ color +" soap");
	    remove_adj(query_adjs());
	    set_adj(({ "worn", "small", adj, color, }));
	    set_long("It is a small soap that can be used to wash the face "+
	      "and body. It is "+ adj +" "+ color +" and has been used until "+
	      "it is rather shapeless. The soap still has a fresh scent and "+
	      "would probably help you feel nice and clean.\n"+
	      " Try <help soap> to learn more.\n");

	    wear = 3;
	}

	return 1;
    }
    else if (val > 0)
    {
	if (wear == 3)
	{
	    add_name("sliver");
	    add_pname("slivers");
	    set_short(adj +" "+ color +" sliver of soap");
	    set_pshort(adj +" "+ color +" slivers of soap");
	    remove_adj(query_adjs());
	    set_adj(({ "worn", "small", adj, color, }));
	    set_long("It is the last sliver of a soap that can be used to "+
	      "wash the face and body. It is "+ adj +" "+ color +" and "+
	      "still has a fresh scent. You can probably get some more "+
	      "use out of it.\n"+
	      "Try <help soap> to learn more.\n");

	    wear = 4;
	}

	return 1;
    }
    else
    {
	tell_room(environment(environment(TO)), "The "+ TO->short() +
	  " melts away as the last of it is used.\n", 0, TO);

	remove_object();
	return 1;
    }

    return 0;
}

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    max_uses = 25 + random(15);
    uses = max_uses;

    set_name("soap");
    set_pname("soaps");
    f_dissolve();
    add_prop(OBJ_I_VALUE,  250);
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 30);
    set_keep(1);

    add_prop(HIZARBIN_OFFERING, 1);

    add_cmd_item("soap", "help",
      "With this soap you may:\n\n"+
      "soapwash    [face]  : Wash away dirt and grime.\n"+
      "            [hands]\n"+
      "            [body]\n\n"+
      "soapscrub   <face>  : Scrub away dirt and makeup.\n"+
      "                      This will also restore your \n"+
      "                      original apprearance if you've \n"+
      "                      altered it at the Ziggurat!\n\n"+
      "soapscrub   <body>  : Wash away dirt, perfume, glitter\n"+
      "                      and anything else coating your skin.\n\n"+
      "soapbubble          : Blow soap bubbles.\n\n");
// Converting to use item_expiration -- Lilith
//  We will always recover.
//    will_not_recover = 0;
	if (IS_CLONE)
      set_item_expiration();  	
}

public void
hook_smelled()
{
    write("It smells "+ smell +".\n");
}

private int
f_wash(string str)
{
    if(str == "face")
    {
	write("You add some water to the soap in your hands "+
	  "and wash your "+ str +" with the lather.\n");

	say(QCTNAME(TP) +" makes a lather from "+
	  HIS(TP) +" "+ short() +" and "+
	  "cleans "+ HIS(TP) +" "+ str +" with it.\n");

	TP->query_subloc_obj("_pomade_kiss_left_cheek_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_right_cheek_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_forehead_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_chin_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_nose_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_lips_")->remove_object();
	TP->query_subloc_obj("kiss_subloc")->remove_object();

	uses -= 1;
	f_dissolve();

	return 1;
    }

    if (str == "hands")
    {
	write("You add some water to the soap in your hands "+
	  "and wash them with the lather.\n");

	say(QCTNAME(TP) +" makes a lather from "+
	  HIS(TP) +" "+ short() +" and "+
	  "cleans "+ HIS(TP) +" "+ str +" with it.\n");

	TP->query_subloc_obj("_pomade_kiss_left_hand_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_right_hand_")->remove_object();

	uses -= 1;
	f_dissolve();

	return 1;
    }

    if (str == "body" || !strlen(str))
    {
	write("You add some water to the soap in your hands "+
	  "and wash all over with the lather.\n");

	say(QCTNAME(TP) +" makes a lather from "+
	  HIS(TP) +" "+ short() +" and "+
	  "cleans "+ HIM(TP) +"self with it.\n");

	if (TP->query_guild_name_occ() == "Union of the Warriors of Shadow")
	{
	    TP->emote_adjust_union_virtue(US_PURITY, 50);
	    TP->add_prop("_Union_cleansed_in_astuary", time());
	}

	TP->query_subloc_obj("_kalad_dirty_subloc")->remove_object();
	TP->query_subloc_obj("wearing_blood_object_subloc")->remove_object();
	TP->query_subloc_obj("_fireplace_soot_subloc_")->remove_object();
	TP->query_subloc_obj("stink_object_subloc")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_left_hand_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_right_hand_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_bottom_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_neck_")->remove_object();
	present("DUNG_OBJ", TP)->remove_object();

	uses -= 1;
	f_dissolve();

	return 1;
    }

    return 0;
}

private int
f_scrub(string str)
{
    int count = 0;

    if (str == "face")
    {
	write("You add some water to the soap in your hands "+
	  "and scrub your "+ str +" with the lather until not "+
	  "a hint of impurity remains.\n");

	say(QCTNAME(TP) +" makes a lather from "+
	  HIS(TP) +" "+ short() +" and "+
	  "cleans "+ HIS(TP) +" "+ str +" with it.\n");

	if (TP->query_guild_name_occ() == "Union of the Warriors of Shadow")
	{
	    TP->emote_adjust_union_virtue(US_PURITY, 50);
	    TP->add_prop("_Union_cleansed_in_astuary", time());
	}

	TP->query_subloc_obj("_rosey_lips")->remove_object();
	TP->query_subloc_obj("_eye_lashes_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_left_cheek_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_right_cheek_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_forehead_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_chin_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_nose_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_lips_")->remove_object();
	TP->query_subloc_obj("kiss_subloc")->remove_object();
	TP->remove_unique_looks();

	uses -= 1;
	f_dissolve();

	return 1;
    }

    if (str == "body")
    {
	write("You add some water to the soap in your hands "+
	  "and scrub all over with the lather, returning your "+
	  "skin to a pure and natural state.\n");

	say(QCTNAME(TP) +" makes a lather from "+
	  HIS(TP) +" "+ short() +" and "+
	  "scrubs "+ HIM(TP) +"self with it.\n");

	if (TP->query_guild_name_occ() == "Union of the Warriors of Shadow")
	{
	    TP->emote_adjust_union_virtue(US_PURITY, 50);
	    TP->add_prop("_Union_cleansed_in_astuary", time());
	}

	TP->query_subloc_obj("_glittery_skin_")->remove_object();
	TP->query_subloc_obj("_kalad_dirty_subloc")->remove_object();
	TP->query_subloc_obj("wearing_blood_object_subloc")->remove_object();
	TP->query_subloc_obj("_fireplace_soot_subloc_")->remove_object();
	TP->query_subloc_obj("_shine_subloc")->remove_object();
	TP->query_subloc_obj("stink_object_subloc")->remove_object();
	TP->remove_prop("_i_am_wearing_a_smell");
	TP->query_subloc_obj("_pal_cologne_krom_subloc")->remove_object();
	TP->query_subloc_obj("_pal_cologne_control_subloc")->remove_object();
	TP->query_subloc_obj("_pal_cologne_whitehammer_subloc")->remove_object();
	TP->query_subloc_obj("_pal_perfume_cosmias_subloc")->remove_object();
	TP->query_subloc_obj("_pal_perfume_tortuous_subloc")->remove_object();
	TP->query_subloc_obj("_pal_perfume_jordessia_subloc")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_left_hand_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_right_hand_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_bottom_")->remove_object();
	TP->query_subloc_obj("_pomade_kiss_neck_")->remove_object();
	TP->remove_perfume();
	present("DUNG_OBJ", TP)->remove_object();
	present("perfume_odor_object ", TP)->remove_object();


	uses -= 1;
	f_dissolve();

	return 1;
    }

    return 0;

}

private int
f_bubbles(string str)
{
    write("You lather the soap and raise it to your lips.\n"+
      "A stream of bubbles floats into the air on the wings "+
      "of your breath.\n");
    say(QCTNAME(TP) +" raises "+ short() +" to "+
      HIS(TP) +" mouth and blows gently on it.\n"+
      "A stream of small soap bubbles floats into the air.\n");

    return 1;
}

private int
f_drop(string str)
{
    if(str == "soap" || str == "the soap")
    {
	write("Uh-oh! You dropped the soap!\nYou feel yourself blushing "+
	  "as you carefully back away from it.\n");

	say("Oops! "+ QCTNAME(TP) +" dropped the soap!\n"+
	  CAP(HE(TP)) +" blushes faintly and carefully backs away from it.\n");

	TO->move(ENV(ENV(TO)));

	return 1;
    }

    return 0;
}

public void
init(void)
{
    ::init();

    if (ENV(TO) != TP)
	return;

    add_action(        f_wash, "soapwash"      );
    add_action(       f_scrub, "soapscrub"     );
    add_action(     f_bubbles, "soapbubble"    );
    add_action(        f_drop, "drop"          );

}

public string
query_recover(void)
{
    return MASTER + ":"+ uses +"#"+ max_uses +"#"+ (wear - 1) +"#"+
	adj +"#"+ color +"#"+ shape +"#"+ emblem +"*" +
	query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    sscanf(arg, "%d#%d#%d#%s#%s#%s#%s*%s", uses, max_uses, wear,
	adj, color, shape, emblem, arg);

    f_dissolve();
}
