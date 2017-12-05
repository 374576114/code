#include <stdio.h>
#include <stdlib.h>

int table[256];
int arc_table[256];
int inv_ta[256];
int i;

void g_exp()
{
    int i;

    table[0] = 1;
    for(i=1; i<255; i++){
        // t[i+1] = t[i]*2
        table[i] = (table[i-1]<<1);
        // mod 与 加余数
        if(table[i] & 0xffffff00)
            table[i] ^= 0x11D;
    }
}

void v_table()
{
    int i;
    for(i=0; i<256; i++)
        arc_table[table[i]] = i;
}

void inv_tab()
{
    int i, k;
    for(i=1; i<256; i++){
        k = arc_table[i];
        k = 255-k;
        k %= 255;
        inv_ta[i] = table[k];
    }
}

int mul(int a, int b)
{
    int a_a = arc_table[a];
    int a_b = arc_table[b];
    int k = (a_a+a_b) % 255;
    printf("%d %d %d\n", k, a_a, a_b);


    return table[k];
}

int main()
{
    int i, j;

    g_exp();
    v_table();
    inv_tab();
    for(i=0; i<16; i++){
        for(j=0; j<16; j++)
            printf("%02x ", table[16*i+j]);
        printf("\n");
    }

    printf("\n");
    for(i=0; i<16; i++){
        for(j=0; j<16; j++)
            printf("%02x ", arc_table[16*i+j]);
        printf("\n");
    }

    printf("\n");
    for(i=0; i<16; i++){
        for(j=0; j<16; j++)
            printf("%02x ", inv_ta[16*i+j]);
        printf("\n");
    }
    printf("%02x\n", mul(0xc2, 7));
    return 0;
}

