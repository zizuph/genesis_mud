/* Barrack base, the base room file for the barracks in VK
 * By Teth, Dec. 3 1996
 */

#include "../../../local.h"

inherit IN_BASE;

public void
reset_vin_room()
{
}

public void
create_barrack()
{

}

nomask void
create_vin_room()
{
    set_short("Barrack in Vingaard Keep");
    set_long("This is one section of the barracks for the militia " +
        "of Vingaard Keep. These are living quarters, as evidenced " +
        "by the beds and the furniture. This room is kept lit with " +
        "a soft glow from torches, due to the continual activity " +
        "of the militia switching shifts. ");
    AI(({"barrack","barracks","quarters","living quarters"}),
        "This place is kept tidy, as befitting an orderly " +
        "military organization.\n");
    AI("bed","One bed is the same as any other.\n");
    AI("beds","The beds are in fair condition, and are kept " +
        "in order when not being used.\n");
    AI("furniture","Standard furniture for barracks, nothing " +
        "much of interest.\n");
    AI("torches","The torches are firmly bolted into the walls, " +
        "so getting them would be impossible.\n");
    AI(({"wall","floor","ceiling"}),"It is made of stone, which " +
        "would most likely be quite cold in a Solamnian winter.\n");
    AI("walls","The walls of the room are constructed of stone.\n");
    
    INSIDE;
    LIGHT;

    create_barrack();
    reset_room();

}

