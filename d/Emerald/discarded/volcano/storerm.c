// Storeroom for herb tent
// Note this holds nothing cause the merchant holds the wares.

inherit "/std/room"
 
create_room()
{
set_short("storeroom");
set_long("This is a storeroom for the herbmerchant\n");
	add_exit("hrbtent.c", "tent");
}
