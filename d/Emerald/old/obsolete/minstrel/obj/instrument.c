inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";
 
public void
create_instrument()
{
}
 
public nomask void
create_object()
{
    create_instrument();
}
 
public int
perform_song(string arg)
{
}
 
public void
init()
{
    ::init();
 
    add_spell("/d/Emerald/minstrel/spell/bravura");
 
    add_spell_object(this_player());
 
    add_action(perform_song, "play");
    add_action(perform_song, "perform");
}
 
public void
remove_object()
{
    ::remove_object();
    cleanup_spells();
}
