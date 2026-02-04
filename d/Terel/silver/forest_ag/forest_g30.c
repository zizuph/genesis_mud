/* File         : /d/Terel/silver/forest/forest_g30.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/forest_base.c
 * Comments     : Basic Silver forest room.
 * Modifications: Added a dead tree with engraved encryption key - for bandit treasure quest - Udana 03/2006
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "forest_base";
int size;
int *key;

/* Creates a new random encryption key */
void create_key();

public void
create_room()
{
    ::create_room();
   set_short("On a small glade in the Silver Forest");
    set_long_desc(random(10));
 
add_my_desc("A single large dead tree is standing in the middle of the glade.\n");
	
    add_exit(FOREST_AG + "forest_f30", "south",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h30", "north",0,random(4),"@@exits");
    add_exit(FOREST_HP + "forest_h29", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_g29", "west",0,random(4),"@@exits");
    add_exit(FOREST_AG + "forest_f29", "southwest",0,random(4),"@@exits");
	
	remove_item("dead tree");
	add_item(({"tree", "dead tree"}), "A dead tree, separated from the others. It must have been standing here "+
		"for ages. You notice some writing engraved on it.\n");
    reset_room();
	create_key();
	
}

void create_key()
{
	size = random(2) + 3;
	key = allocate(size);
	for(int i = 0; i < size; ++i)
	{
		key[i] = random(sizeof(LETTERS));
	}
}	

public void init()
{
	::init();
	add_action("display_key", "read");
}

int display_key(string a)
{
	string player_key = "";
	player_key += size;
	if(a == "writing")
	{
		write("  ");
		for(int j = 0; j < size; ++j)
			write("/\\");
		write("_\n");
		write("  |");
		for(int j = 0; j < size; ++j)
		{
			write(LETTERS[key[j]] + " ");
			player_key += LETTERS[key[j]];
		}
		write("|\n");
		write("  ");
		for(int j = 0; j < size; ++j)
			write("\\/");
		write("~\n");
		TP->add_prop(PLAYER_M_T_KEY, player_key);
		return 1;
	}
 return 0;
}
