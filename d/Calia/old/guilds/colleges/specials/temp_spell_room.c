/*
    This is a in-between room used for delayed effects, for instance
    when a fire efreet is on its way to deliver a message.
*/

inherit "/std/room";

create_room()
{
    set_short("Waiting room.");

    set_long("This room is used in the spell code for the Colleges."+
        " A mortal finding him or herself here should immediately" +
        " contact the guildmaster.\n");
}