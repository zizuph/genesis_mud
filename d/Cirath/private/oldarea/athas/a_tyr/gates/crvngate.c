/* crvngate: Tyr's western gate: Serpine, 12-04-96 */
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"
                        
void
reset_room()
{
    bring_room_team(TYR_NPCS+"tmpl_mid.c", 1, 2, ATH_PERSON+"hgiant.c", 1); 
}
 
void
create_room()
{
    set_short("inside Caravan Gate");
    set_long("This dark and massive tunnel through the city wall is "
            +"capable of supporting all but the most gigantic wagons. "
        +"A massive block of stone sits in an alcove to the north.\n");
 
    add_item(({"block","stone","massive block","massive block of stone"}),
             "It's large enough to block off the tunnel, and has huge "
            +"steel rings attached.\n");
 
    add_item(({"ring","rings","steel rings","steel ring","huge steel rings"}),
            "They are bigger then the hand of a half-giant.\n");
 
    add_exit(TZ_CARAVAN+"rd_cw_01.c", "east", "@@sun_flash@@", 1);
    add_exit(PASS+"plain01.c", "west", "@@sun_flash@0", 1);
 
    reset_room();
}
 
public int
sun_flash()
{
    TP->catch_msg("You are blinded as you again enter "
                 +"the brightness of the Athasian sun.\n");
    return 0;
}
