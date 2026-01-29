/*
 *  Pax Tharkas, Ground level, Small cell.
 *  cell.c
 *  
 *  Coded ........: 2003/02/26
 *  By ...........: Blizzard
 *
 */


#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include "/d/Krynn/qualinesti/local.h"

inherit PAXINROOM;

int       got_weapon(object player);
void      release_elf();
int       is_weapon(object weapon);
int       try_cut(string str);
int       try_release(string str);
int       light_torch(string what);
int       ext_torch(string what);

object elf;
int gReleased, light_intens;

#define I_RELEASED_ELF       "_i_released_elf"
#define LOST_SCOUTS          "_lost_scouts"
#define ELF_CAMP_QUEST       "_elf_camp_quest"

reset_pax_room()
{
    light_intens = 1;
    add_prop(ROOM_I_LIGHT, light_intens);
    
    gReleased = 0;
    if ( !(elf = present("sarist", TO)) )
    {
        elf = clone_object(NPC + "sarist.c");
        elf->move_living(0, this_object());
    }

}
         
int
query_prisoner()
{
   if ( present("sarist", TO) )
       return 1;
   else
       return 0;
}

void
create_pax_room()
{
   object door;
   
   reset_pax_room();

   set_short("Small cell");
   set_long("@@room_descr");
	
   add_item("holder", 
       "An iron torch holder placed on the west wall. There is a large " +
       "torch mounted in it.\n");
   add_item( ({ "torch", "large torch" }), "@@torch_descr" );

   set_alarm(30.0, 240.0, "do_flicker");

   door = clone_object("/d/Krynn/qualinesti/move_to_pax/celldoor1");
   door->move(TO);   

   INSIDE;
//   add_exit("/w/blizzard/test/guard_room", "west", 0);
//   add_exit(GROUND_LEVEL + "guard_room", "west", 0);
}


string
room_descr()
{
    if ( light_intens )
    {
        return "This is a small room within the walls of Pax Tharkas. There " +
            "are no windows and the only light source is a flickering " +
            "torch, placed in an iron holder on the west wall, next to " +
            "the door leading to the guard room, thus it is quite dark " +
            "and cold here. This place is probably used as a temporary " +
            "cell for prisoners, before they are thrown into lower levels " +
            "of the fortress or served as a dinner for the dragon.\n";
    }
    else
    {
        return "This is a small room within the walls of Pax Tharkas, " +
            "probably used as a temporary cell for prisoners before " +
            "they are thrown into lower levels of the fortress or served " +
            "as a dinner for the dragon. Because of the lack of " +
            "windows it is quite dark and cold here. There is an unlit " +
            "torch placed in an iron holder on the west wall, next to " +
            "the door leading to the guard room.\n"; 
    }

}
   
string
torch_descr()
{
    if ( light_intens == 0 )
    {
        write("It's a rather large unlit torch solidly placed in an " +
            "iron holder on the west wall.\n");
    }
    else
    {
        write("It's a rather large lit torch solidly placed in an " +
            "iron holder on the west wall. It flickers slightly as " +
            "it burns.\n");
    }
    return "";

}

void
init()
{
    ::init();
    ADD(try_cut, "cut");
    ADD(light_torch, "light");
    ADD(ext_torch, "extinguish");
    ADD(try_release, "release");
    
}

int
light_torch(string what)
{
   if (what == "torch")
   {
      if (light_intens == 0)
      {
         light_intens = 1;
         write("You light the large torch.\n");
         say(QCTNAME(TP) + " lights the large torch.\n");
         add_prop(ROOM_I_LIGHT,light_intens);
      }  
      else
      {
         write("But .. It's already lit.\n");
      }
      return 1;
   
   }
   else
   {
      NF("Light what?\n");
      return 0;
   }
}
   

int
ext_torch(string what)
{
   if (what == "torch")
   {
      if (light_intens == 1)
      {
         light_intens = 0;
         write("You extinguish the large torch.\n");
         say(QCTNAME(TP) + " extinguishes the large torch.\n");
         add_prop(ROOM_I_LIGHT, light_intens);
      }
      else 
      {
         write("But .. The torch isn't lit.\n");
      }

      return 1;
   }
   else
   {
      NF("Extinguish what?\n");

      return 0;
   }
}

void
do_flicker()
{
   if(light_intens == 1)
   {
      tell_room(TO, "The burning torch flickers, casting strange " +
                    "shadows on the wall.\n");
   }
}

void
release_elf()
{    
    write("You cut the rope bounding the elf, releasing him.\n");
    say(QCTNAME(TP) + " cuts the rope bounding the prisoner.\n");
    
    gReleased = 1;
    elf->set_released(1);
    elf->remove_descr();
    
    if ( TP->query_prop(LOST_SCOUTS) )
    { 
        TP->add_prop(I_RELEASED_ELF, 1);
    }
    else if ( TP->query_prop(ELF_CAMP_QUEST) )
    {
        TP->add_prop(I_RELEASED_ELF, 1);
        elf->command("say Ha!");
        elf->command("extinguish torch");
        elf->command("open door");
        elf->command("west");
    }

}

/* Function name   : is_weapon
 * Description     : We check if the player is wielding a slashing weapon
 * Returns         : 1     if player is wielding slashing weapon
 *                   0     in other cases
 */
int
is_weapon(object weapon)
{
    if ( !objectp(weapon))
        return 0;
    
    if ( !weapon->check_weapon() )
        return 0;
        
    if ( weapon->query_wielded() != TP )
        return 0;
    
    return ( weapon->query_dt() & W_SLASH );
}

/* Function name   : got_weapon
 * Description     : We check if the player has any slashing weapon
 */    
int
got_weapon(object player)
{
    mixed *items = player->query_weapon(-1);
    int   n = -1;
    
    if ( !objectp(player) )
        return 0;
    
    if ( !sizeof(items) )
        return 0;
        
    while (++n < sizeof(items))
    {
        if ( items[n]->query_dt() & W_SLASH)
            return 1;
    }
    
    return 0;
}

int
try_release(string str)
{
    if ( !CAN_SEE_IN_ROOM(TP) )
    {
        notify_fail("It is too dark to see.\n");
        return 0;
    }
    
    if ( !strlen(str) )
    {
        notify_fail("Release who?\n");
        return 0;
    }
    
    if ( !elf )
    {
        notify_fail("Whom are you trying to release?\n");
        return 0;
    }
    
    if ( present("sarist", TO) && gReleased == 1 )
    {
        notify_fail("But the prisoner has been already released.\n");
        return 0;
    }
    
    if ( present("sarist", TO) && gReleased == 0 )
    {
        write("You have to cut the rope to release him.\n");
        return 1;
    }
    
}

/* Function name   : try_cut
 * Description     : We try to cut the rope that bounds the elf
 */    
int
try_cut(string str)
{
    string  what, wep;
    
    if ( !elf )
    {
        notify_fail("Cut what?\n");
        return 0;
    }

    if ( !CAN_SEE_IN_ROOM(TP) )
    {
        notify_fail("It is too dark to see.\n");
        return 0;
    }
            
    if ( present("sarist") && gReleased == 1 )
    {
        notify_fail("But the rope bounding the elf has been cut already.\n");
        return 0;
    }
            
    if ( !strlen(str) )
    {
        notify_fail("Cut what?\n");
        return 0;
    }
    
    if ( sscanf(str, "%s with %s", what, wep) == 2 )
    {
        if ( what != "rope" )
            notify_fail("Cut what?\n");

        else if ( objectp(present(wep, TP)) )
        {
            if ( is_weapon(present(wep, TP)) )
            {
                release_elf();
                
                return 1;
            }
            
            notify_fail("You are not wielding any " + wep + ".\n");
        }
        else
            notify_fail("You do not have any " + wep + ".\n");
        
        return 0;
    }
    
    if ( str == "rope" )
    {
        if ( !got_weapon(TP) )
        {
            write("You are not wielding anything sharp enough to cut " +
                "the rope with!\n");
            say(QCTNAME(TP) + " tries to cut the rope, but he has nothing " +
                "sharp enough to cut with.\n", TP);
        
            return 1;
        }
        
        release_elf();
        
        return 1;
    }
    
    return 0;
    
}

