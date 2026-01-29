/*
   Pax Tharkas, Ground level, Guard room.

   guard_room.c
   ------------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 3/06/2003
   By ...........: Blizzard
   For quest purposes.
*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define FOUND_SWORD        "_found_sword"
#define LOST_SCOUTS        "_lost_scouts"
#define ELF_CAMP_QUEST     "_elf_camp_quest"
#define CELL_ROOM          PTHARKAS + "ground_level/cell"

object guard1, guard2, guard3, guard4, guard5, guard6;
object door;
int    sword_picked, sword_found, cell = 0;
void   set_cell_loaded();
int    query_cell_loaded();

void
set_cell_loaded()
{
    seteuid(getuid(TO));
    (CELL_ROOM)->load_me();
    cell = 1;
}

int
query_cell_loaded()
{
    if ( cell == 1 )
        return 1;
    else
        return 0;
}

int
guards_present()
{
   if (present("aurak",TO) || present("bozak",TO) || present("sivak",TO))
      return 1;

   return 0;
}


reset_pax_room()
{
   sword_picked = 0;
   sword_found  = 0;
   
   if ( query_cell_loaded() == 0 )
      set_cell_loaded();
      
   if (!guards_present())
   {
      guard1 = clone_object(PMONSTER + "aurak");
      guard2 = clone_object(PMONSTER + "sivak");
      guard3 = clone_object(PMONSTER + "sivak");
      guard4 = clone_object(PMONSTER + "bozak");
      guard5 = clone_object(PMONSTER + "bozak");
      guard6 = clone_object(PMONSTER + "bozak");

      guard2->set_leader(guard1);
      guard3->set_leader(guard1);
      guard4->set_leader(guard1);
      guard5->set_leader(guard1);
      guard6->set_leader(guard1);

      guard1->team_join(guard2);
      guard1->team_join(guard3);
      guard1->team_join(guard4);
      guard1->team_join(guard5);
      guard1->team_join(guard6);

      guard1->move(TO);
      guard2->move(TO);
      guard3->move(TO);
      guard4->move(TO);
      guard5->move(TO);
      guard6->move(TO);
      guard6->command("close door");
   }
}
         

void
create_pax_room()
{
   reset_pax_room();

   set_short("Guard room");
   set_long("@@room_descr");
	
   INSIDE;

   add_item(({"table", "tables"}), "@@table_descr");
   add_item( "middle table", "@@middle_table" );
   add_item(({"rack", "racks", "weapon rack", "weapon racks"}), "These " +
            "are large weapon and armour racks. By the look of them " +
            "they could probably hold swords, spears, and different " +
            "sorts of armour. Right now they hold nothing.\n");
   
   add_search("middle table", 1, "middle_table", 1);

   add_exit(GROUND_LEVEL + "corridor3", "south",0);
   door = clone_object(POBJ + "celldoor2");
   door->move(TO);

}

string 
table_descr()
{
    string ret_str = ".\n";
    
    if ( sword_picked )
        ret_str = "You find nothing interesting there.\n";
    
    if ( sword_found )
        ret_str = "Something is laying on the middle table.\n";
    
    if ( !sword_found )
    {
        tell_room(TO, QCTNAME(TP) + " looks around the room and " + HIS(TP) +
            " sight stops on the middle table.\n", TP);
        ret_str = "You notice something laying on the middle table.\n";
        sword_found = 1;
    }
    
    return "You move your sight from one table to another. They are made " +
        "of rough wood. Someone has been handling heavy equipment on " +
        "them, leaving them scarred. " + ret_str ;

}  

mixed
search_mid_table(object searcher, string what)
{
    if ( guards_present() )
        return "A draconian stops you from doing that.";

    if ( sword_picked )
        return 0;
    
    tell_room(TO, QCTNAME(searcher) + " picks a sword from the " +
        "middle table.\n", searcher);
    
    if ( searcher->query_prop(LOST_SCOUTS) )
        searcher->add_prop(FOUND_SWORD, 1);

    clone_object("/d/Krynn/qualinesti/wep/ok_blade")->move(searcher);
    sword_picked = 1;
        
    return "You examine the weapon, that is laying on the middle table. " +
        "To your surprise, this long sword is obviously of elven making. " +
        "You decide to take it.\n";

}
        
string
middle_table()
{
    if ( guards_present() )
    {
        tell_room(TO, "A draconian scowls at " + QTNAME(TP) + " and says: " +
            "What are you looking for? Begone!\n", TP);
        return "A draconian scowls at you and says: What are you looking " +
            "for? Begone!\n";
    }
    
    if ( sword_picked )
        return "This big table is made of rough wood. You find nothing " +
            "interesting on it.\n";
    
    tell_room(TO, QCTNAME(TP) + " comes closer to the middle table " +
        "and takes a long sword from it.\n", TP);
    
    if ( TP->query_prop(LOST_SCOUTS) )
        TP->add_prop(FOUND_SWORD, 1);

    clone_object("/d/Krynn/qualinesti/wep/ok_blade")->move(TP);
    sword_picked = 1;
        
    return "You come closer to the middle table and examine an item, " +
        "that is laying on it. To your surprise it is a long sword, " +
        "obviously of elven making. You decide to take it.\n";
         
}
   
string
room_descr()
{
   string ret_str;

   if (guards_present())
      ret_str = "You have stumbled right into a guard room.";
   else
      ret_str = "You are standing in the middle of a guard room. " +
                "Luckily there are no guards in here at the moment.";

   return ret_str + " This is a wide and well kept room. Wooden tables " +
                    "made of rough wood are placed along the walls. On " +
                    "each side of each table there is a bench. This room " +
                    "could easily contain a dozen guards. Weapon racks " + 
                    "are standing against the wall at both sides of the " +
                    "entrance.\n";
}
   
void
enter_inv(object dest, object old)
{
    object drac;
    
    ::enter_inv(dest, old);
    
    if ( (drac = present("draconian", TO)) )
        drac->command("close door");
        
    if ( guards_present() && dest->id("sarist") )
    {
        dest->command("shout Die filthy drac!");
        dest->command("kill draconian");
    }    

}

