#include <vector>
#include <map>
#include <emscripten/emscripten.h>
#include <stdio.h>

extern "C"
{
    int EMSCRIPTEN_KEEPALIVE bocchi_shut_up(int flag, int *seq, int size)
    {
        int max_show = -1;
        int max = -1;
        bool f = false;
        std::map<int, int> mp;
        for (int i = 0; i < size; ++i)
        {
            if (seq[i] > 9 && (seq[i] / 10) % 10 == flag)
            {
                if (mp.find(seq[i]) == mp.end())
                {
                    mp[seq[i]] = 1;
                    if (mp[seq[i]] > max_show)
                    {
                        max_show = mp[seq[i]];
                        max = seq[i];
                        f = false;
                    }
                    else if (mp[seq[i]] == max_show)
                    {
                        f = true;
                    }
                }
                else
                {
                    mp[seq[i]]++;
                    if (mp[seq[i]] > max_show)
                    {
                        max_show = mp[seq[i]];
                        max = seq[i];
                        f = false;
                    }
                    else if (mp[seq[i]] == max_show)
                    {
                        f = true;
                    }
                }
            }
        }
        return f ? 10 : max;
    }
}
