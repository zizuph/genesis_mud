/* /d/Raumdor/common/temple/lair1.c 
*
*Lair of the Khiraa 
*
*
* Refurbishing the original khiraa lair2
*
* Nerull 2020
*
*/
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

#define UNDULL_CLEAVER   "/d/Raumdor/magical_weapons/2h_undull_beast_cleaver"
#define UNDULL_MACE      "/d/Raumdor/magical_weapons/2h_undull_beast_mace"
#define LIFE_ROBE        "/d/Raumdor/common/arm/doomguard_robe"


string
query_k_rune()
{
    //if(IS_LP(TP) || IS_DK(TP))
      //  return "They are praises to the Nameless one. All hail "+
        //"unto Him. The portal of Death awaits.\n";
    return "Some of the runes are quite ancient and you don't "
    +"know what they say, but there is a new set of scribblings "
    +"near the runes, saying: Decayed " 
    +"grinning skull resting on a scythe...the mark on an item of "
    +"war, forever shall "
    +"you be warped, forever shall you last! You who bear the mark "
    +"must be sacrificed in the living flame!\n";
}


void
create_room()
{
    ::create_room();
	
	seteuid(getuid());
	
	add_prop(ROOM_I_LIGHT,1);
	
    set_short("A foul chamber");
    
    set_long("\n   You now find yourself in a grim looking chamber. The "+
    "walls here are all made of black stone, and there are numerous markings "+
    "on them. The ceiling is higher up here, and you can see what "+
    "appears to be a floating orb near the very top. It is glowing "+
    "a bright purple, lighting up the entire room. The floor is "+
    "made of black polished marble, and there is a large red grim "+
    "skull painted on it.\n"+
    "   In the center of the red grim skull is a large, black altar. "+
    "The altar itself is made of stone, and has many interesting "+
    "markings on it. There is an eerie green flame errupting from "+
    "the center of the altar, flaring with intensity. Next to the "+
	"altar, there is an empty black wooden "+
    "stand. The air is filled with "+
    "death and decay, and a chill that sinks right down to your bones. "+
    "You feel that there is great magic at work here.\n\n");
   
    add_item("walls","The walls are made of cold black stone, and are "+
    "smooth to the touch. Upon them, many mysterious red runes are "+
    "carved in.\n");
	
    add_item("floor","The floor is made of polished black marble, and "+
    "painted on it is a large, red grim skull, the center of which "+
    "sits a large black altar.\n");
	
    add_item("ceiling","The ceiling is high here, and is slightly "+
    "vaulted. At the very top, right over the large black altar, "+
    "you see a floating orb.\n");
	
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
	
    add_item(({"skull","red skull","red grim skull","grim skull"}),
    "The large red skull seems to be a painting. It looks ghastly. "+
    "In the center of its mouth, the large black altar sits.\n");
	
    add_item(({"orb","floating orb"}),"The floating orb radiates "+
    "a purple glow that illuminates the room somewhat. It hovers "+
    "over the eerie green fire that is flaring over the large "
	+"black altar.\n");
	
	add_item(({"flame","eerie flame", "eerie green flame", 
	"green flame", "forge"}),"The eerie green flame errupts from the "
	+"center of the large black altar by magical means. It soars towards "
	+"the ceiling, like a fire in a forge. For some reason, the "
    +"eerie green flame feels sentient and aware of your presence. You "
    +"are not sure if you dare to ask it for help though.\n");
	
    add_item(({"large altar","large black altar","black altar","altar"}),
    "The large black altar is made of solid black marble. On it, you "+
    "see many red runes and symbols. The surface is perfectly smooth, "+
    "but you can see what appears to be dried blood on it. In its center "
	+"an eerie green flame flaring with intensity, resembling some sort of "
	+"a magical forge.\n");
		
	add_exit(TEMPLE_DIR + "lair8", "west", 0);
}


int aid_response(object playah)
{
    playah->catch_tell("The eerie green flame whispers to "
    +"you: Bring me the items of war that carries the mark "
    +"of the Reaper! Sacrifice them here! I crave it...I "
    +"demand it! The magical powers they possess I will "
    +"consume!\n");
    
    return 1;
}


int
ask_flame(string str)
{
    if (str == "flame task" 
    || str == "green flame task" 
    || str == "eerie flame task"
    || str == "eerie green flame task"
    || str == "flame quest"     
    || str == "green flame quest" 
    || str == "eerie flame quest" 
    || str == "eerie green flame quest"
    || str == "flame help" 
    || str == "green flame help" 
    || str == "eerie flame help" 
    || str == "eerie green flame help")
    {
        set_alarm(1.0, 0.0, &aid_response(this_player()));
        
        return 1;
    }
    
    return 0;
}

int
sacrifice_item(string str)
{
	if (!str)
	{
		write("Sacrifice what?\n");
		return 1;
	}
	
	if (str == "black death robe" || str == "black robe" 
	|| str == "death robe" || str == "robe")
	{
		object token, token2;
		
		if (objectp(token = present("black_death_robe", this_player())))
        {
			write("You sacrifice the black death robe into the eerie green flame. "
			+"Without warning, your "
			+token->query_short()+" vanishes for a second, for then to return to the "
			+"altar in a different appearance. You greedily take the dim purple robe "
			+"from the altar!\n");
			
            tell_room(environment(this_player()), "The "+
            token->query_short()+" of "+
            QTNAME(this_player())+" vanishes for a second, only to return to the altar in "
			+"a different appearance, which "+QTNAME(this_player())
			+" greedily picks up!\n", this_player());
			
            token->remove_object();
			
			token2 = clone_object(LIFE_ROBE);
			token2->move(this_player(), 1);
			
			return 1;
        }
	}
    
	if (str == "rust-red spiked mace" || str == "rust-red mace" || str == "mace")
	{
		object mace, mace2;
		
		if (objectp(mace = present("rust_red_spiked_mace", this_player())))
        {
			write("You sacrifice the rust-red spiked mace into the eerie green flame. "
			+"Without warning, your "
			+mace->query_short()+" vanishes for a second, for then to return to the "
			+"altar in a warped state. You greedily take the warped rust-red spiked mace "
			+"from the altar!\n");
			
            tell_room(environment(this_player()), "The "+
            mace->query_short()+" of "+
            QTNAME(this_player())+" vanishes for a second, only to return to the altar in "
			+"a warped state, which "+QTNAME(this_player())
			+" greedily picks up!\n", this_player());
			
            mace->remove_object();
			
			mace2 = clone_object(UNDULL_MACE);
			mace2->move(this_player(), 1);
			
			return 1;
        }
	}
	
	if (str == "rust-red heavy cleaver" || str == "rust-red cleaver" || str == "cleaver")
	{
		object cleaver, cleaver2;
		
		if (objectp(cleaver = present("rust_red_heavy_cleaver", this_player())))
        {
			write("You sacrifice the rust-red heavy cleaver into the eerie green flame. "
			+"Without warning, your "
			+cleaver->query_short()+" vanishes for a second, for then to return to the "
			+"altar in a warped state. You greedily take the warped rust-red heavy cleaver "
			+"from the altar!\n");
			
            tell_room(environment(this_player()), "The "+
            cleaver->query_short()+" of "+
            QTNAME(this_player())+" vanishes for a second, only to return to the altar in "
			+"a warped state, which "+QTNAME(this_player())
			+" greedily picks up!\n", this_player());
			
            cleaver->remove_object();
			
			cleaver2 = clone_object(UNDULL_CLEAVER);
			cleaver2->move(this_player(), 1);
			
			return 1;
        }
	}
	
	write("You sense that the eerie green flame will not accept "
	+"that.\n");
	
	return 1;
}


void
init()
{
    ::init();
    add_action(sacrifice_item,"sacrifice");
    add_action(ask_flame, "ask");
}




