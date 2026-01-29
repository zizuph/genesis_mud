/* 
 * Dirty drinking water
 * Altrus, May 2005
 */

inherit "/std/drink";

void create_drink()
{
    set_name("water");
    set_pname("waters");
    set_adj(({"glass of", "dirty"}));
    set_short("glass of dirty water");
    set_pshort("glasses of dirty water");
    set_long("A glass of disgustingly dirty, brown water.\n");
    set_soft_amount(80);
}
