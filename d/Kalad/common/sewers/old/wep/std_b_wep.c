inherit "/d/Kalad/std/weapon.c";


int
wield(object wep)
{
    write("You feel very secure as you wield the " + short() + ".\n");
    return 0;
}

int 
unwield(object wep)
{
    write("You feel sad to depart from the " +short()+ ".\n");
    return 0;
}


