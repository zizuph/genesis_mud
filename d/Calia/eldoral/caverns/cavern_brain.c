#pragma strict_types

int war_count,
    kni_count;

public void
reset_counters()
{
    war_count = 20 + random(20);
    kni_count = 5 + random(5);
}

public void
create()
{
    reset_counters();
}

public int
query_count(int i)
{
    if (!i)
        return war_count;
    else if (i == 1)
        return kni_count;
}

public int
mod_count(int i, int val)
{
    if (!i)
        return war_count += val;
    else if (i == 1)
        return kni_count += val;
}
