#include <iostream>
#include <vector>

// ================= Abstrakcje (Payment) =================
struct Payment;

using PayFunc = void(*)(Payment*, int);

struct Payment
{
    const char* name;  // nazwa płatności
    PayFunc pay;
};

void CreditCardPay(Payment* p, int amount)
{
    std::cout << p->name << " payment: " << amount << "\n";
}

void BankTransferPay(Payment* p, int amount)
{
    std::cout << p->name << " payment: " << amount << "\n";
}

void EWalletPay(Payment* p, int amount)
{
    std::cout << p->name << " payment: " << amount << "\n";
}

// ================= Implementacje (PaymentGateway) =================
struct PaymentGateway;

using ProcessFunc = void(*)(PaymentGateway*, int);

struct PaymentGateway
{
    const char* name;   // nazwa bramki
    Payment* payment;   // referencja do abstrakcji
    ProcessFunc process;
};

void PayPalProcess(PaymentGateway* g, int amount)
{
    std::cout << "[" << g->name << "] Processing payment...\n";
    g->payment->pay(g->payment, amount);
}

void GarminPayProcess(PaymentGateway* g, int amount)
{
    std::cout << "[" << g->name << "] Processing payment...\n";
    g->payment->pay(g->payment, amount);
}

void GooglePayProcess(PaymentGateway* g, int amount)
{
    std::cout << "[" << g->name << "] Processing payment...\n";
    g->payment->pay(g->payment, amount);
}

void handle()
{
    std::cout << "--- Dynamic Bridge (Casey-style) ---\n\n";

    // Tworzymy różne płatności
    Payment creditCard{ "CreditCard", CreditCardPay };
    Payment bankTransfer{ "BankTransfer", BankTransferPay };
    Payment eWallet{ "EWallet", EWalletPay };

    // Tworzymy bramki i przypisujemy płatności
    std::vector<PaymentGateway> gateways = {
        { "PayPal", &creditCard, PayPalProcess },
        { "GarminPay", &creditCard, GarminPayProcess },
        { "GooglePay", &bankTransfer, GooglePayProcess },
        { "PayPal", &bankTransfer, PayPalProcess },
        { "GarminPay", &eWallet, GarminPayProcess }
    };

    // Dynamiczne wykonywanie płatności
    for (auto& gateway : gateways)
    {
        gateway.process(&gateway, 100);  // kwota 100
        std::cout << "-------------------------\n";
    }

    // Przykład zmiany implementacji w locie
    std::cout << "\n--- Changing Payment dynamically ---\n";
    gateways[0].payment = &bankTransfer;
    gateways[0].process(&gateways[0], 250);
}
