/* temple/obj/gold_key.c is cloned by temple/obj/soap.c */
inherit "/std/key";
 
void
create_key()
{
    set_name("key");
    add_name("_ring_quest_key_");
    add_adj("gold");
    set_short("gold key");
    set_long("A gold key.\n");
    set_key("ringq_door");
}
