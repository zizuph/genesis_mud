#include <tasks.h>

inherit "/std/object";

void
create_object()
{
    set_name("checker");
    add_name(({"task","tasker"}));
    set_short("Task checker");
}

void
task(int diff)
{
    int i,a,b;
    float p,q;
    for(i=0;i<410;i+=10)
    {
	a=diff-2*i;
	if(a>500) b=1000-a;
	else b=a;
	if (b<0) p=0.0;
	else p=itof(2*b*(2*b+1))/20020.0;
	if (a>500) q=100.0-p;
	else q=p;
	q=100.0-q;
	write(sprintf("%3i  %O\n",i,q));
    }
}

/* calc chance of random(a) > random(b) */
void
rnd_ch(int a, int b)
{
    float c=itof(a),d=itof(b);
    write("Chance: random(" + a + ") > random(" + b + "):\n");
    dump_array(100.0*c/2.0/(c/2.0+d/2.0));
}

void
resolve_chance(int diff, int skill)
{
    int td=diff-2*skill;
    int ch,sw=0;
    write("D: " + diff + " S: " + skill + " => ");
    if (td > 500)
    {
	td = 1000 - td;
	sw=1;
    }
    ch = 2*td*(2*td+1)/20020;
    if (td<=0)
	write("0");
    else if (td<=500)
    {
	if (sw)
	    write("" + ch);
	else
	    write("" + (100 - ch));
    }
    else
	write("error");
    write("\n");
}

void
resolve(int diff, int skill)
{
    int min = 100*(1+2*skill-diff)/diff;
    int max = 100*(999+2*skill-diff)/diff;
    int avg = 100*(500+2*skill-diff)/diff;
    write("MIN: " + min);
    write(" MAX: " + max);
    write(" AVG: " + avg);
    write("\n");
}

