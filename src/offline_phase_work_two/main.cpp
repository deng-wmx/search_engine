#include <iostream>
#include <vector>
#include "../../include/offline_phase_work_two/Configuration.h"
#include "../../include/offline_phase_work_two/RSS.h"
#include "../../include/offline_phase_work_two/RemoveDuplicates.h"
#include "../../include/offline_phase_work_two/SimHash.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

int main(int argc, char* argv[]) {
    
    /* Configuration configuration; */
    /* RSS rss(100); */
    /* // 这一步会把清洗后的网页文件和偏移文件都做好 */
    /* rss.buildPage(&configuration, "../../data/page.dat"); */
    /* RemoveDuplicates remove; */
    /* remove.buildOffSite(); */
    
    SimHash simhash;
    cout << simhash.compareStr("111", "111") << "\n";
    

    Mylogger::destroy();
    return 0;
}

