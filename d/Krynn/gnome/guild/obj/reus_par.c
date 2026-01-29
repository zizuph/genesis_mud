/* The ReusablePartsModule is cloned when destructing items with
 * the gnomish Recycler (available for the gizmo).
 * First you will get the item with set_no_show() but once you
 * recycled enough material, you will get the module ready for action.
 * This you may use to build several interesting objects!
 * Created by Dajala                                    20.02.1995
 */

inherit "/std/object";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"


/* Global variables */

string  *materials = allocate(5), already_there = "",
	name = "_rpm_", /* Three states: '_rpm_' --- not shown
			   'reusablepartsmodule' --- shown, not built
				   'flumadiddle' --- built */
	*parts = ({"spring", "wheel", "gear", "cog", "triphammer",
		"string", "flag", "tube", "pipe", "bell",
		"knob", "horn", "whistle", "shim"}),
	*adj   = ({"tiny", "small", "midsized", "large", "flexible",
		"stiff", "flat", "thick", "coloured", "smooth"});
int     mat_count = 0,  /* How many materials are there in the list */
	input = 0,      /* How many items recycled */
	built_flag = 0, /* Built a flumadiddle ? */
	*items = allocate(20), item_count,    /* For the parts included */
	long_desc,      /* Determines the random long description */
	volume, presented = 0, number_of_uses;


/* Prototypes */

void end_assemble(object player);

void
create_object()
{
    set_name("_reusable_parts_module_");        /* Always the same */
    add_name("_rpm_");                     /* Changes with state */
    set_short("ReusablePartsModule");
    set_long("@@mylong");
    set_no_show();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GIVE, "@@no_give");
    add_prop(OBJ_M_NO_DROP, "@@no_give");
}

string
no_give()
{
   return "You could never part with your " + C(query_short()) + ".\n"; 
}

string
mylong()
{
    string str, parts_desc = "", mat_desc = "";
    int i;

    if(TP->query_race_name() != "gnome")    
	return "A fascinating collection of assorted parts, it's hard to see "
		+ "any structure in. Only a gnome could have produced that.\n";
    for(i=0;i<item_count;i+=2) 
    {                        
	if(i == 2)
		parts_desc = " and " + parts_desc;
	if(i > 2)
		parts_desc = ", " + parts_desc;
	parts_desc = adj[items[i]] + " " + parts[items[i+1]]
		+ "s" + parts_desc;
    }
    if(!built_flag)
    {
	if(materials[0])
	   mat_desc = materials[0];
	if(mat_count)
	   mat_desc = materials[1] + " and " + mat_desc;
	for(i=2;i<mat_count;i++)   
		mat_desc = materials[i] + ", " + mat_desc;
	if(mat_desc != "")
		mat_desc = " and scattered traces of " + mat_desc;
	str = "A fascinating collection of assorted parts, it's hard to see "
	    + "any structure in.\n"
	    + "But nevertheless your sharp gnomish eyes can "
	    + "identify some " + parts_desc 
	    + mat_desc + ".\nYou may <arrange> the module or "
	    + "<assemble> a thingumabob, whatsit, contraption, fluma"
	    + "diddle, domajig, whaddayacallit or widget, which you "
	    + "then may <admire> for yourself or <present> to admiring "
	    + "bystanders. Eventually you may <disassemble> your creation.\n";
    }
    else        /* We built a flumadiddle */
    {
	if (!long_desc)
	   {     
		str = "An intriguing " + C(name) + " constructed "
			+ "from several " + parts_desc + ", while its purpose"
			+ " is not, at this moment, entirely clear.\n";
	   }
	if (long_desc == 1)
	   {     
		str = "A " + C(name) + ", cunningly contrived "
			+ "from several " + parts_desc + ". It's a most "
			+ "impressive invention, although its function "
			+ "is not immediately apparent.\n";
	   }
	if (long_desc == 2)
	   {     
		str = "A fascinating " + C(name) + ", cleverly "
			+ "assembled from some " + parts_desc + ". The urge "
			+ "to tinker with it is almost irresistable.\n";
	   }
	if (long_desc == 3)
		str = "An engrossing combination of many " + parts_desc
			+ ". One could spend hours tinkering with this "
			+ C(name) + ".\n";

	/* Mylong() is called as well when the item is presented to others.
	 */ 
	if(!presented)
		str = str + "You may <admire> it or <present> it to admiring "
		   + "bystanders. Eventually you may <disassemble> your "
		   + "creation.\n";
    }
    return str;
}

/* Unfortunately even the fun with a flumadiddle is limited.
 */

void
wear_out(object player)
{
    number_of_uses = number_of_uses + 6 - 
			ftoi(itof(player->query_skill(SS_BUILD))/33.0);
    if(number_of_uses > 15)
    {
	player->command("oops");    
	if(built_flag)
		player->catch_msg("Your " + C(name));
	else
		player->catch_msg("Your ReusablePartsModule");
	player->catch_msg(" suddenly desintegrates into a heap of parts "
		+ "which one after the other falls from your hands and "
		+ "piles on the ground.\n");
	tell_room(E(player), "Something suddenly falls from "
		+ QCTNAME(player) + "s hands and piles on the "
		+ "ground.\n", player);
	seteuid(getuid());
	clone_object(GOBJ + "junk")->move(E(player));
	remove_object();
    }
}

/* Cleaning your Module regularly prolonges its lifetime.
 * Called from the soul.
 */

void
reduce_wear_out()
{
   if(number_of_uses > 0)
	number_of_uses--;
}

void
init()
{
    if(E(TO)->query_race_name() == "gnome")
    {
	ADA("assemble");
	ADA("arrange");
	ADD("present_mod", "present");
	ADA("disassemble");
	ADA("admire");
    }
}

/* Adds a recognized material to the list. 
 * Called from the soul.
 */

void
add_material(string new_mat)
{
   int i;

   //write("new_mat = " + new_mat);
   for(i=0;i<sizeof(materials);i++)
	if(materials[i] == new_mat)
		return;
   
   if(mat_count < 5)
   {     
	materials[mat_count] = new_mat;
	mat_count++;
   }
}

/* Adds volume to the to-be ReusablepartsModule
 */

void
add_volume(int vol)
{
   volume += vol;
}

/* Checks whether there is enough material for a new ReusablePartsModule
 * and updates the parameters.
 * Called from the soul each time something is being recycled.
 */

void
check_complete(object player)
{
   if(item_count < 20)
   {
	items[item_count] = random(sizeof(adj));
	items[item_count + 1] = random(sizeof(parts));
	item_count += 2;
   }
   input++;
   
   if(((input > (7 + random(4))) || (query_prop(OBJ_I_WEIGHT) > 10000)) 
	&& query_no_show())
   {
	add_name("reusablepartsmodule");
  	add_name("ReusablePartsModule");
      name = "reusablepartsmodule";
	remove_name("_rpm_");
	add_prop(OBJ_I_VOLUME, volume);
	player->catch_msg("A whistle sounds!\n"
		+ "The shutter opens again and you receive "
		+ "your new ReusablePartsModule.\n");
	tell_room(E(player), "You hear a whistle.\n", player);
	unset_no_show();
	set_no_show_composite(0);
   }
   else
	add_prop(OBJ_I_VOLUME, (query_prop(OBJ_I_VOLUME)) 
		+ volume);
   volume = 0;
}

/* A nice emote. Nothing else...
 */

int
arrange(string str)
{
    if(built_flag || query_no_show())
	return 0;
    NF("Arrange what? The ReusablePartsModule?\n");
    if(C(str) != "Reusablepartsmodule" && C(str) != "ReusablePartsModule" 
	&& str != "module")
	return 0;

    write("You tidily arrange your collection of parts inspecting each "
	+ "in turn.\n");
    say(QCTNAME(TP) + " tidily arranges a collection of odd bits and "
	+ "pieces inspecting each one in turn.\n");
    return 1;
}

/* Assemble the parts to a new flumadiddle! ;) 
 */

int
assemble(string str)
{
    int a;

    if(built_flag || query_no_show())
	return 0;
    NF("Assemble what?\n");
    str = lower_case(str);
    if((str != "whatsit") && (str != "contraption") && (str != "flumadiddle")
	&& (str != "domajig") && (str != "whaddayacallit") 
	&& (str != "thingumabob") && (str != "widget"))
		return 0;

    name = str;
    a = 5 + random(3);
    set_alarm(5.0, -1.0, "assemble_msg", TP, a, 4);
    "/d/Krynn/gnome/guild/obj/kgnome_soul.c"->paralyze_player(TP,
	"You are too occupied assembling your " + C(str) + ".\n", "",
	5 + a*5);
    write("You start assembling a brand new " + C(str) + ".\n");
    say(QCTNAME(TP) + " starts working over something.\n");
    return 1;
}

string
get_part()
{
   int a;

   a = random(item_count / 2);
   already_there = adj[items[2*a]] + " " + parts[items[(2*a)+1]];
   return already_there;
}

void
assemble_msg(object player, int count, int last_a) 
{
   int a;
   string str1, str2, str3;
   
   a = random(12);
   if(a == last_a)    /* Never give out the same twice */
   {     
	assemble_msg(player, count, last_a);
	return;
   }
   if(!count)
   {     
	end_assemble(player);
	return;
   }

   if (!a)
	{
	   player->catch_msg("You attach a part.\n");
	   tell_room(E(player), QCTNAME(player) + " attaches a part.\n"
		, player);
	}
   if (a == 1)
	{
	   player->catch_msg("Whistling an abstracted tune you inspect "
		+ "your work in progress.\n");
	   tell_room(E(player), "While whistling an abstracted tune, "
		+ QCTNAME(player) + " inspects " 
		+ POSSESSIVE(player) + " work in progress.\n", player);
	}
   if (a == 2)
	{
	   str1 = get_part();

	   do {str2 = get_part();}
	   while (str2 == str1);
	   
	   player->catch_msg("With reckless abandon, you suddenly add a "
		+ str1 + " and " + ({"two", "three", "four"})[random(3)] 
		+ " " + str2 + "s to your " + C(name) + ".\n");
	   tell_room(E(player), "With reckless abandon, " 
		+ QCTNAME(player) + " suddenly adds a "
		+ str1 + " and some " + str2 + "s to " + POSSESSIVE(player) 
		+ " creation.\n", player);
	}
   if (a == 3)
	{
	   str1 = get_part();

	   player->catch_msg("You add " + ({"three", "four", "five"})[random(3)] 
		+ " " + str1 + "s to the " + C(name) + ".\n");
	   tell_room(E(player), QCTNAME(player) + " adds another few "
		+ str1 + "s to " + POSSESSIVE(player) + " creation.\n"
		, player);
	}
   if (a == 4)
	{
	   if (already_there == "")          
	   {     
		assemble_msg(player, count, last_a);
		return;
	   }

	   player->catch_msg("You frown at the " + C(name) + " and remove a "
		+ already_there + ".\n");
	   tell_room(E(player), QCTNAME(player) + " frowns at "
		+ POSSESSIVE(player) + " creation and removes a " 
		+ already_there + ".\n", player);

	   already_there = "";
	}
   if (a == 5)
	{
	   str1 = get_part();

	   do {str2 = get_part();}
	   while (str2 == str1);
	   
	   player->catch_msg("You piece together a " + str1 + " and a "
		+ str2 + ", then connect them both to the " + C(name) + ".\n");
	   tell_room(E(player), QCTNAME(player) + " pieces together a "
		+ str1 + " and a " + str2 + ", then connects the to " 
		+ POSSESSIVE(player) + " creation.\n", player);
	}
   if (a == 6)
	{
	   if (already_there == "")          
	   {     
		assemble_msg(player, count, last_a);
		return;
	   }
	   player->catch_msg("You wriggle a recently-attached "
		+ already_there + " and look thoughtful.\n");
	   tell_room(E(player), QCTNAME(player) + " wriggles a recently-"
		+ "attached " + already_there + " and looks thoughtfully.\n"
		, player);
	}
   if (a == 7)
	{
	   player->catch_msg("You rotate the " + C(name) + " looking for "   
		+ "flaws.\n");
	   tell_room(E(player), QCTNAME(player) + " rotates "
		+ POSSESSIVE(player) + " work looking for flaws.\n", player);
	}
   if (a == 8)
	{
	   str1 = get_part();
	   
	   player->catch_masg("You affix a " + str1 + " to the assembly.\n");
	   tell_room(E(player), QCTNAME(player) + " affixes a " + str1
		+ " to " + POSSESSIVE(player) + " work.\n", player);
	}
   if (a == 9)
	{
	   player->catch_msg("You squint at the internals of the " + C(name)
		+ ", then give a satisfied nod.\n");
	   tell_room(E(player), QCTNAME(player) + " squints at the internals "
		+ " of " + POSSESSIVE(player) + " work, then gives a "
		+ "satisfied nod.\n", player);
	}
   if (a == 10)
	{
	   
	   if (already_there == "")          
	   {     
		assemble_msg(player, count, last_a);
		return;
	   }
	   player->catch_msg("You give the " + already_there + " a sharp "
		+ "tug, it flies off in a random direction and disappears.\n");
	   tell_room(E(player), QCTNAME(player) + " gives a " + already_there
		+ " a sharp tug, it flies off in a random direction and "
		+ "disappears.\n", player);
	   already_there = "";
	}
   if (a == 11)
	{
	   if (already_there == "")          
	   {     
		assemble_msg(player, count, last_a);
		return;
	   }
	   player->catch_msg("You remove a " + already_there + ", then "           
		+ "reattach it to the other side of the " + C(name) + ".\n");
	   tell_room(E(player), QCTNAME(player) + " removes a " + already_there
		+ " from " + POSSESSIVE(player) + " work, then reattaches "
		+ "it again to the other side.\n", player);
	}
    set_alarm(5.0, -1.0, "assemble_msg", player, count - 1, a);
}

void
end_assemble(object player)
{
   player->command("cheer");
   player->catch_msg("You finished your " + C(name) + ".\n");
   tell_room(E(player), QCTNAME(player) + " finishes " + POSSESSIVE(player)
	+ " work and smiles gleefully.\n", player);
   built_flag = 1;
   set_short(name);
   add_name(name);
   remove_name("reusablepartsmodule");
   remove_name("ReusablePartsModule");
   long_desc = random(4);       /* Random Description */
   set_alarm(20.0, -1.0, "wear_out", player);
}

int
admire(string str)
{
   int a;

   if(!built_flag)
	return 0;        
   NF("Admire what?\n");
   if(lower_case(str) != name)
	return 0;

   a = random(4);
   if(!a)
   {
	TP->catch_msg("You turn the " + C(name) + " over and "
		+ "over in your hands and smile proudly.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns " + POSSESSIVE(TP)
		+ " " + C(name) + " over and over in " + POSSESSIVE(TP)
		+ "hands and smiles proudly.\n", TP);
	return 1;
   }
   if(a == 1)
   {
	TP->catch_msg("You hold the " + C(name) + " aloft and "
		+ "glow with pride.\n");
	tell_room(E(TP), QCTNAME(TP) + " holds " + POSSESSIVE(TP)
		+ " " + C(name) + " aloft and glows with pride.\n"
		, TP);
	return 1;
   }
   if (a == 2)
   {
	TP->catch_msg("You gaze admiringly at the " + C(name)
		+ ".\n");
	tell_room(E(TP), QCTNAME(TP) + " gazes admiringly at "
		+ POSSESSIVE(TP) + " " + C(name) + ".\n", TP);
   	return 1;
   }
   write("You gaze at the " + C(name) + " and preen yourself on "
	+ "its clearly superior design and implementation.\n");
   say(QCTNAME(TP) + " gazes at " + POSSESSIVE(TP) + " " + C(name)
	+ " and preens " + OBJECTIVE(TP) + "self on its clearly "
	+ "superior design and implementation.\n");
   return 1;
}

int
present_mod(string str)
{
   string *arg;
   object target;

   if(!built_flag)
	return 0;        
   NF("Present what to whom?\n");
   if(sizeof(arg = explode(str, " ")) != 3)
	return 0;
   if((lower_case(arg[0]) != name) || (arg[1] != "to") ||
	       (!objectp(target = P(arg[2], E(TP)))))
	return 0;

   presented = random(3) + 1;

   if (presented == 1)
	{
	   TP->catch_msg("You hold your " + C(arg[0]) + " scant inches "
		+ "away from " + target->query_the_name(TP) + "'s nose so "
		+ PRONOUN(target) + " may properly admire it.\n");
	   target->catch_msg(TP->query_The_name(target) + " holds something scant inches "
		+ "away from your nose so you may properly admire it.\n"
		+ "You see " + lower_case(mylong()));
	   tell_room(E(target), QCTNAME(TP) + " holds " + POSSESSIVE(TP)
		+ " " + arg[0] + " scant inches from " + QCTNAME(target)
		+ "'s nose so " + PRONOUN(target) + " may properly admire it.\n", 
		({target, TP}));
	}
   if (presented == 2)
	{
	   TP->catch_msg("You tug firmly on " + target->query_the_name(TP)
		+ "'s sleeve to draw " + POSSESSIVE(target) + " attention to "
		+ "your " + C(arg[0]) + ".\n");
	   target->catch_msg(TP->query_The_name(target) + " tugs firmly on your sleeve to draw "
		+ "your attention to " + POSSESSIVE(TP) + " " + C(arg[0]) + ".\n");
	   tell_room(E(target), QCTNAME(TP) + " tugs firmly on "
		+ QCTNAME(target) + "'s sleeve to draw " + POSSESSIVE(target)
		+ " attention to " + POSSESSIVE(TP) + " " + C(arg[0]) + ".\n",
		({TP, target}));
	}
   if (presented == 3)
	{
	   TP->catch_msg("You nudge " + target->query_the_name(TP)
		+ " sharply and point towards your " + C(arg[0]) + ".\n");
	   target->catch_msg(TP->query_The_name(target) + " nudges you sharply and points "
		+ "towards " + POSSESSIVE(TP) + " " + C(arg[0]) + ".\n");
	   tell_room(E(target), QCTNAME(TP) + " nudges " + QCTNAME(target)
		+ " sharply and points towards " + POSSESSIVE(TP) + " "
		+ C(arg[0]) + ".\n", ({TP, target}));
	}
   presented = 0;
   return 1;
}

int
disassemble(string str)
{
   string str1, str2;
   
   if(!built_flag)
	return 0;
   NF("Disassemble what?\n");
   if(lower_case(str) != name)
	return 0;

   str1 = get_part();
   do {str2 = get_part();}
   while (str2 == str1);
   
   write("You begin to disassemble your " + C(str) + ". You remove a "
	+ str1 + " or two, tug sharply on a " + str2 + " and the " 
	+ C(str) + " suddenly collapses into a jumbled collection of parts.\n");
   say(QCTNAME(TP) + " begins to disassemble " + POSSESSIVE(TP) + " "
	+ C(str) + " but suddenly the whole apparatus collapses into a "
	+ "jumbled collection of parts.\n");

   built_flag = 0;
   set_short("ReusablePartsModule");
   add_name("reusablepartsmodule");
   add_name("ReusablePartsModule");
   remove_name(name);
   name = "reusablepartsmodule";
   set_alarm(20.0, -1.0, "wear_out", TP);
   return 1;
}

/* What did we build?
 * Called from the soul. (Module 8)
 */
string
get_name()
{
   return name;
}

/* For Testing: Have a new module fast! :)
 */
string
patch_module()
{
   input = 10;
   return "Ok. Input = 10";
}
