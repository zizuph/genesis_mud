/*
 * pike.c
 * Not a weapon, can stab a skull, be lodged into the ground and lit on fire.
 * 
 * Ares, 2004
 *
 */

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h";

/*This is a prototype - if we know the names of functions in the class (file)*/
/*then we declare them at the top*/

string short_description();
string long_description();
int do_lodge(string str);
int do_burn();
int do_stab();
int do_normal();
int flame_tongue();
int remove_object();



/*This are class level variables - every function in this file can see it*/

string description1 = "An older style pike used in wars long ago. "+
"It's probably not much use for a weapon anymore.";
string description2 = "An older style pike used in wars long ago. "+
"It's not much use for a weapon anymore but this one seems "+
"to have been used to send someone a message.";
string description3 = "An older style pike used in wars long ago. "+
"It's not much use for a weapon anymore but this one seems "+
"to have been used to send someone a message. It has been set "+
"on fire. ";
int state_of_pike = 0;
string skull_race = "";
string skull_adj1 = "rotting";
int has_a_skull = 0;

void
create_object()
{
    /*This is a function level variable, only the function*/
    /*called "create_object()" knows what this variable is*/

    string name_string = "pike";
    add_name("_pike_");

    /*We use the function level (also known as local) variable*/
    /*only inside the function it is declared in*/

    set_name(name_string);

    set_short("@@short_description@@");

    /*The @@ symbols are a VBFC call - it's a function that is called */
    /*every time a player interacts with the object (so every time */
    /*a player look at this pike, we'll call the function long_description()*/
    /*to determine what the pike looks like*/

    set_long("@@long_description@@"+"\n");


    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,2);
}

string
short_description()
{
    if (has_a_skull)
    {
	return "long pike with a "
	+ skull_adj1
	+ " "
	+ skull_race 
	+ " skull impaled on top";
    } else {
	return "long pike";
    }
}

string
long_description()
{
    /*here is a local string we set the class level one*/
    /*we do that because we want to add a tag onto the end if there*/
    /*is a skull on the pike*/

    string descrip = "";

    if (state_of_pike == 0)
    {
	descrip = description1;
    }

    if (state_of_pike == 1)
    {
	descrip = description2;
    }

    if (state_of_pike == 2)
    {

	descrip = description3;
    }

    /*now that we have the first sentence of the long descrip, we can*/
    /*add on more sentences if needed - so we check for a skull*/

    if (has_a_skull)
    {
	/*there's a skull, so add it's description onto the end*/
	descrip += "  There is a " 
	+ skull_adj1 
	+ " " 
	+ skull_race
	+ " skull impaled on the pike.";
    }

    return descrip;

}

void
init()
{
    ::init();
    add_action(do_lodge,"lodge");
    add_action(do_burn,"burn");
    add_action(do_stab,"stab");
    add_action(do_normal,"normal");

}

int
do_normal()
{
    write("You change the pike back to normal.\n");
    has_a_skull = 0;
    skull_adj1 = "rotting";
    skull_race = "";
    state_of_pike = 0;

    return 1;
}

int
do_stab()
{
    /*define the local variables*/
    object ob;

    if (has_a_skull == 1)
    {
	notify_fail("There is not enough room for more than one skull!\n");
	return 0;
    }

    /*set the local object to a skull in our inventory*/
    ob = present("skull",this_player());

    /*If we found a skull, we can use it!*/
    if (ob)
    {
	write("You take a skull and impale it on your pike!\n");
	SAY(" takes a skull and impales it on "+ HIS(TP) +" pike!");

	/*set our class skull description race string*/
	skull_race = ob->query_race();

	/*set our int to 1 so we'll display the skull in our description*/
	has_a_skull = 1;

	/*remove the skull from their inventory, or if it was a pile*/
	/*of skulls, just subtract one of them!*/

	skull_adj1 = "rotting";

	if (ob->num_heap() > 1)
	{
	    ob->set_heap_size(ob->num_heap() - 1);
	} else 
	{
	    ob->remove_object();
	}

	/*return*/
	return 1;
    }

    /*we didn't find a skull, so fail*/
    NF("You don't have a skull to impale!\n");
    return 0;

}

int
do_lodge(string str)
{
    /*You can make anything happen, but we're just changing the description*/
    /*by changing the class level INT to a 1*/

    if (environment(environment(this_object()))->query_prop(ROOM_I_INSIDE))   
    { 
	write("You cannot lodge the pike indoors!\n");
	return 1;  
    }


    if (!has_a_skull)
    {
	notify_fail("This pike would pose quite a hazard for anyone who doesn't "+
	  "know it is here, you decide not to take that risk.\n");
	SAY(" is about to lodge the pike into the ground but has second thoughts.");
	return 0;
    }

    if (state_of_pike == 1)
    {
	notify_fail("It's already lodged deep into the ground!\n");
	return 0;
    }

    if (state_of_pike == 2)
    {
	notify_fail("It's already lodged deep into the ground!\n");
	return 0;
    }

    if (present("_pike_", environment(this_player()))) 
    { 
	write("There is a pike here already!\n"); 
	return 1; 
    }




    NF("Lodge what?\n");
    if(str != "pike into ground")
	return 0;
    skull_adj1 = "rotting";
    state_of_pike = 1;
    write("Mustering all your strength, you force the pike into the ground. \n");
    SAY(" brutally forces the pike into the ground.  ");

    //object spear//
    //spear = this_object()//
    this_object()->add_prop(OBJ_M_NO_GET, "Its stuck in the ground!\n");
    this_object()->add_prop(OBJ_I_NO_STEAL, "Its stuck in the ground!\n");
    this_object()->move(environment(this_player()));
    this_object()->set_short(this_object()->short()+" is lodged into the ground");


    /*return 1 to say processing should stop*/	
    return 1;
}

int
do_burn()
{
    /*basically the same as do lodge*/


    if (!has_a_skull)
    {
	notify_fail("There isn't anything to burn on it!\n");
	return 0;
    }

    if (!state_of_pike == 1)
    {
	notify_fail("You have to lodge the pike into the ground first!\n");
	return 0;
    }

    if (state_of_pike == 2)
    { 
	notify_fail("The pike is already on fire! \n");
	return 0;

    }

    if (present("torch",this_player()))
    {
	write("With the torch, you light the pike on fire!\n");
	SAY(" sets the pike on fire! ");

	set_short("flaming "+ short());
	state_of_pike = 2;
	skull_adj1 = "burning";

	reset_euid();

	set_alarm(4.0, 70.0, "flame_tongue");   
	set_alarm(2000.0, 0.0, "remove_object");



	return 1;
    }

    notify_fail("You need a torch to light it on fire!\n");
    return 0;
}

void
flame_tongue()
{

    tell_room(environment(),"Smoke rises from the burning skull, causing eerie shadows on the ground.\n");

}

void
remove_object()
{

    tell_room(environment(),"The pike burns to the ground and is gone.\n");

::remove_object();
}
