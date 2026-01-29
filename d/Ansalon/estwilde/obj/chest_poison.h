poison = clone_object("/std/poison_effect");
if(poison)
{
    poison->move(enemy);
    poison->set_time(2400);
    poison->set_interval(10);
    poison->set_strength(20);
    poison->set_damage(({POISON_FATIGUE, 175, POISON_HP, 15}));
    poison->start_poison();
}
