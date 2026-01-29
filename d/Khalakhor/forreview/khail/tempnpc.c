inherit "/std/creature";

public int
set_acc_exp(int stat, int val)
{
    ::set_acc_exp(stat,val);
}
public void
create_creature()
{
    set_name("dwarf");
    set_race_name("dwarf");
}
