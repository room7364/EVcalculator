#include "../../omp/EquityCalculator.h"
#include <iostream>
using namespace omp;
using namespace std;
int main()
{
    EquityCalculator eq;
    vector<CardRange> ranges{"QQ+,AKs,AcQc", "A2s+", "random"};
    uint64_t board = CardRange::getCardMask("2c4c5h");
    uint64_t dead = CardRange::getCardMask("Jc");
    double stdErrMargin = 2e-5; // stop when standard error below 0.002%
    auto callback = [&eq](const EquityCalculator::Results& results) {
        cout << results.equity[0] << " " << 100 * results.progress
                << " " << 1e-6 * results.intervalSpeed << endl;
        if (results.time > 5) // Stop after 5s
            eq.stop();
    };
    double updateInterval = 0.25; // Callback called every 0.25s.
    unsigned threads = 0; // max hardware parallelism (default)
    eq.start(ranges, board, dead, false, stdErrMargin, callback, updateInterval, threads);
    eq.wait();
    auto r = eq.getResults();
    cout << endl << r.equity[0] << " " << r.equity[1] << " " << r.equity[2] << endl;
    cout << r.wins[0] << " " << r.wins[1] << " " << r.wins[2] << endl;
    cout << r.hands << " " << r.time << " " << 1e-6 * r.speed << " " << r.stdev << endl;
}