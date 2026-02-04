// Key for the warroom in the stronghold fortk.c
// Tomas  -- Jan 2000.

inherit "/std/key";

create_key()
{
    ::create_key();

    set_short("iron engraved key");
    set_pshort("iron engraved keys");
    set_adj(({"iron","engraved"}));
   
    add_item(("engraving"),"The engraving is of two axes crossed together.\n");

    set_long("It's a iron engraved key.\n");
}
