/* /d/Faerun/guilds/warlocks/rooms/racks.c
 *
 * Rack room in the guildhall.
 *
 * Nerull, 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

object rack;


string tapestry()
{
    if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
    || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return "The large tapestry depicts nothing but swirling "
        +"colours, made from human hair.\n";
    }
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            return "The large tapestry depicts the Archfiend 'Asmodeus', "
            +"the Lord of the Nine Hells. He looks like he is over "
            +"thirteen feet tall, and looks handsome, strong, very "
            +"cunning, and has lustrous skin and black hair. His eyes "
            +"are crimson and shine with with internal power while "
            +"being fixed at You, and his forehead is crowned with "
            +"mall, sharp horns. Asmodeus is wearing red and black "
            +"robes which are studded with black diamonds and fiery "
            +"red rubies.\n";
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            return "The large tapestry depicts the Archfiend 'Asmodeus', "
            +"the Lord of the Nine Hells. He looks like he is over "
            +"thirteen feet tall, and looks handsome, strong, very "
            +"cunning, and has lustrous skin and black hair. His eyes "
            +"are crimson and shine with with internal power while "
            +"being fixed at You, and his forehead is crowned with "
            +"mall, sharp horns. Asmodeus is wearing red and black "
            +"robes which are studded with black diamonds and fiery "
            +"red rubies.\n";
        }
    }
    
    return "The large tapestry depicts nothing but swirling "
    +"colours made from human hair.\n";
}


int
do_stasis(string str)
{
    if (str == "pentagram" || str == "inverted pentagram")
    {
        if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
        || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
        || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
            clone_object(WARLOCK_OBJ_DIR + "invis_paralyze")->move(this_player(), 1);
        
            write("As you touch the small inverted pentagram, you "
            +"suddenly fade from view, becoming completely "
            +"invisible! You enter some magical stasis that prevents "
            +"you from doing anything except observing the environment "
            +"undetected!\n");

            return 1;
        }

        write("You reach for the small inverted pentagram, but a sudden "
        +"unexplainable dreadful feeling stops you from touching it! Maybe "
        +"it's not ment for mere followers...\n");
        
        return 1;
    }
    
    return 0;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("In a rough claystone cave");
    
    set_long("In a rough claystone cave. A huge rack of polished "
    +"metal used for storing weapons, armours and other equipment "
    +"is the most prominent feature in this rather empty cave. Several "
    +"demon-shaped iron sconces line the top of the walls, strongly "
    +"illuminating the entire room with magical crimson light that also "
    +"provides an almost unbearable heat. A large tapestry hangs on the "
    +"west wall.\n");
   
    add_item(({"cave"}),
    "The cave is slightly claustrophobic and unpolished. Judging by the "
    +"appearance of it, you think it was dug out or expanded on natural "
    +"erosion. The cave serves as the general storage area for the "
    +"warlocks.\n");
    
    add_item(({"wall", "walls"}),
    "The walls are rough and jagged due to natural erosion. Several "
    +"demon-shaped sconces line the top of the walls. A huge "
    +"metal rack stands in proximity to the north wall, while a large "
    +"tapestry hangs on the west wall.\n");
    
    add_item(({"ceiling", "roof"}),
    "The claystone ceiling is rough and jagged. It reflects the hellish "
    +"crimson light radiating from the demon-shaped sconces.\n");
    
    add_item(({"ground", "floor"}),
    "The ground is swept for dust and other debris. Several marks "
    +"of fallen weaponry are visible close to the huge metal rack.\n");
    
    add_item(({"mark", "marks"}),
    "Clearly, somebody has been clumsy and dropped sharp weapons "
    +"onto the ground here.\n");
    
    add_item(({"pentagram", "inverted pentagram"}),
    "The pentagram is inverted and carved into the left side of "
    +"the rack. It's about the size of a gold coin in "
    +"diameter. You notice several finger marks around and on top "
    +"of it.\n");
    
    add_item(({"fingerprints", "fingermarks", "finger marks"}),
    "The fingermarks are all over the carved inverted pentagram, as "
    +"if it's been frequently touched for some reason.\n");
    
    add_item(({"heat"}),
    "The heat is almost unbearable. The magical crimson light emitted "
    +"from the flames of the demon-shaped iron sconces make this "
    +"cave feel like you are in some part of hell.\n");
    
    add_item(({"light", "magical crimson light", "crimson light", 
    "magical light"}),
    "The flames erupting from the demon-shaped iron sconces are "
    +"by no means natural. There is no doubt that powerful magic "
    +"enhances them manifold in intensity regarding heat "
    +"radiation, but they are also given a "
    +"crimson light, reminding you about hellfire.\n");
    
    add_item(({"demon-shaped iron sconces", "iron sconces", 
    "demon-shaped sconces", "pit-fiend", "pit-fiends", "sconces"}),
    "The iron sconces line the top of the walls and they are shaped like "
    +"the pit-fiends of Baator. Red-hot magical Flames emitting light and "
    +"heat spill out from the eyes and mouth of the pit-fiends, "
    +"illuminating the cave with a magical crimson light.\n");
    
    add_item(({"tapestry", "large tapestry"}), tapestry);
       
    room_add_object("/d/Faerun/guilds/warlocks/obj/rack");

    add_exit(WARLOCK_ROOMS_DIR + "start", "south");

    reset_faerun_room();
}


void
do_whispers()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()) 
    || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
    || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return;
    }
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers, as "
            +"if something or someone is beckoning you in this "
            +"location!\n");
            
            return;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {  
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("You hear strange whispers, as "
            +"if something or someone is beckoning you in this "
            +"location!\n");
            
            return;
        }
    }
 
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(0.5, 0.0, &do_whispers());
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void init()
{
    ::init();

    add_action(do_stasis, "touch");
}

