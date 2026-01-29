
/* 
	*Maggot's turnip field in the Marish
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit BASE_COMMON;
inherit AREA_ROOM;

void make_npcs();

static object *hobbits = allocate(3);

void create_area_room()
{
	areadesc = "large turnip field";
	area = "in";
	areaname = "the Marish";
	land = "Eriador";
	areatype = 0;
	extraline = "There are probably more turnips here than " +
	"in the whole of the Shire. Best not pick them, farmers " +
	"can be quite protective of their crops! You are standing " +
	"in a row of planted turnips in the northeast corner of " +
	"the field.";
	
	set_add_field();
	set_add_rows_north();
	set_add_rtells();
	
	add_exit(FIELD_DIR + "maggotfield20", "west");
	add_exit(FIELD_DIR + "maggotfield13", "south", 0, 3, 1);
	
	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(int index = 0; index < 3; index++)
    {
        if (!objectp(hobbits[index]))
        {
		hobbits[index] = clone_object(NPC_DIR + "farm_hand");
		hobbits[index]->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(hobbits[index]->query_nonmet_name()))+ " ambles into the general area.\n");
		hobbits[index]->set_restrain_path("/d/Shire/maggot/rooms");
		hobbits[index]->set_random_move(4);

        }
    }

}
