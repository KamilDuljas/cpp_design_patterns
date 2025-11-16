#include <iostream>
#include <memory>
#include <vector>

// Abstraction
class Payment
{
public:
    virtual void pay(int amount) = 0;
    virtual ~Payment() = default;
};

class CreditCard : public Payment
{
public:
    void pay(int amount) override
    {
        std::cout << "Credit card payment: " << amount << "\n";
    }
};

class BankTransfer : public Payment
{
public:
    void pay(int amount) override
    {
        std::cout << "Bank transfer payment: " << amount << "\n";
    }
};

class EWallet : public Payment
{
public:
    void pay(int amount) override
    {
        std::cout << "E-Wallet payment: " << amount << "\n";
    }
};

// Implementation
class PaymentGateway
{
protected:
    std::shared_ptr<Payment> _payment;

public:
    PaymentGateway(std::shared_ptr<Payment> p) : _payment(p) {}
    virtual void process(int amount) = 0;
};

class PayPal : public PaymentGateway
{
public:
    PayPal(std::shared_ptr<Payment> p) : PaymentGateway(p) {}
    void process(int amount) override
    {
        std::cout << "Process for PayPal\n";
        _payment->pay(amount);
    }
};

class GarminPay : public PaymentGateway
{
public:
    GarminPay(std::shared_ptr<Payment> p) : PaymentGateway(p) {}
    void process(int amount) override
    {
        std::cout << "Process for GarminPay\n";
        _payment->pay(amount);
    }
};

class GooglePay : public PaymentGateway
{
public:
    GooglePay(std::shared_ptr<Payment> p) : PaymentGateway(p) {}
    void process(int amount) override
    {
        std::cout << "Process for GooglePay\n";
        _payment->pay(amount);
    }
};

class Bridge
{
public:
    static void handle()
    {
        std::cout << "---Design pattern: Bridge implementation---\n\n";

        auto bankTransfer = std::make_shared<BankTransfer>();
        auto eWallet = std::make_shared<EWallet>();
        auto creditCard = std::make_shared<CreditCard>();

        std::vector<std::shared_ptr<PaymentGateway>> gateways;

        gateways.push_back(std::make_shared<PayPal>(creditCard));
        gateways.push_back(std::make_shared<GarminPay>(creditCard));
        gateways.push_back(std::make_shared<GooglePay>(creditCard));

        gateways.push_back(std::make_shared<PayPal>(bankTransfer));
        gateways.push_back(std::make_shared<GarminPay>(bankTransfer));
        gateways.push_back(std::make_shared<GooglePay>(bankTransfer));

        gateways.push_back(std::make_shared<PayPal>(eWallet));
        gateways.push_back(std::make_shared<GarminPay>(eWallet));
        gateways.push_back(std::make_shared<GooglePay>(eWallet));

        for (auto &gateway : gateways)
        {
            gateway->process(12345);
        }
    }
};