//-*-C++-*-
// file name:      key.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
inherit "/std/key";

void
create_key() 
{
    ::create_key();

    set_adj(({"ornate", "iron"}));

    set_pshort("ornate iron keys");

    set_long("An ornate iron key.\n");


    add_prop("_key_i_no_keyring",1);
    
    set_key(6661666);
}
