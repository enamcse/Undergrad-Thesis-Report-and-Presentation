void find_minimizers(string s, unordered_map<long long, bool > &ret) // reduced a parameter which was actually an index to count efficiently a minimizer in a range
{
    ret.clear();
    if (SZ(s) < K or SZ(s) < W)
    {
        if (SZ(s) < W) cerr << "Sequence Length is smaller than W after inserting gap(-).\n";
        else cerr << "Sequence Length is smaller than K after inserting gap(-).\n";
        return ;
    }
    int n = SZ(s), pos = -1, st, en;
    long long temps, minimizer, prevmin = -1;
    deque<my_data> sliding_window;
    temps = pat2num2(s.substr(0, K));
    sliding_window.push_back(my_data(temps, 0));
    int i ;
    //cerr << num2pat(temps, ((K / 3) * 2)) << " " << temps << endl;
    for (i = K; i < n && i < W; ++i)
    {
        if (s[i] != '_')
        {
            temps <<= 2;
            temps &= kmask;
            temps |= nt2num(s[i]);
        }
        minimizer = temps;
        //cerr << num2pat(temps, ((K / 3) * 2)) << "++" << num2pat(minimizer, ((K / 3) * 2)) << endl;
        while ((!sliding_window.empty()) && minimizer < sliding_window.back().minim)
            sliding_window.pop_back();
        sliding_window.push_back(my_data(minimizer, (i - K + 1)));
    }
    st = 0;
    en = i - 1;
    prevmin = sliding_window.front().minim;
    pos = sliding_window.front().idx;
    //cerr << i << "++" << endl;
    for (; i < n; i++)
    {
        if (s[i] != '_')
        {
            temps <<= 2;
            temps &= kmask;
            temps |= nt2num(s[i]);
        }
        if (s[i - K] != '_') continue;
        minimizer = temps;
        while ((!sliding_window.empty()) && sliding_window.front().idx <= (i - W))
        {

            sliding_window.pop_front();
        }
        while ((!sliding_window.empty()) && minimizer < sliding_window.back().minim)
            sliding_window.pop_back();
        sliding_window.push_back(my_data(minimizer, (i - K + 1)));

        if (sliding_window.front().minim == prevmin)
        {
            en = i - 1;
            pos = sliding_window.front().idx;
        }
        else
        {

            if (ret.count(prevmin) == 0)
            {
                ret[ prevmin ] = true;
            }
            prevmin = sliding_window.front().minim;
            st = i - W + 1;
            en = i;
            pos = sliding_window.front().idx;
        }

    }
    if (sliding_window.front().minim == prevmin)
    {
        en = i - 1;
        pos = sliding_window.front().idx;
    }

    if (ret.count(sliding_window.front().minim) == 0)
    {
        ret[ prevmin ] = true;
    }
    return ;
}