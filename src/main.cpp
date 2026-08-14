const std::vector<unsigned char> stub = { 0xB8, 0x45, 0x00, 0x00, 0x00, 0xC3 }; //mov EAX, 69; ret

#include <Windows.h>

auto main( ) -> int {
    std::println( "Hello, World!" );

    LPVOID juice = VirtualAlloc(nullptr, stub.size(), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (juice == nullptr) { std::println("failed to allocate memory for the stub.."); return 1; }
    
    std::memcpy(juice, stub.data(), stub.size());

    int (*call_stub)() = reinterpret_cast<int(*)()>(juice);

    std::println("stub returned: {}", call_stub());
    return 0;
}
