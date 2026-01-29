public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string dam_descr;
    if (staff_enchanted && dam && !random(4))
    {
	switch(dam)
	{
	case 0..75:   dam_descr = "scorched"; break;
	case 76..150: dam_descr = "burnt";    break;
        default:      dam_descr = "seriously burnt";
	}
	wielder->catch_msg(QCTNAME(enemy)+ " is "+dam_descr+
		  " by the flames surrounding your " +short()+ ".\n");
	enemy->catch_msg("You are "+dam_descr+ " by the flames "+
		  "surrounding " +QTNAME(wielder)+ "'s " +short()+ ".\n");
	wielder->tell_watcher(QCTNAME(enemy)+ " is " +dam_descr+ 
		  " by the flames surrounding " +QTNAME(wielder)+ "'s "+
		  short()+ ".\n", enemy);
	enemy->heal_hp(-dam);
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
