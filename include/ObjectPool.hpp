#pragma once
#include <memory>
#include <vector>
#include <tuple>
#include <utility>

template <typename Object, typename... Args>
class ObjectPool
{
    private:
        static constexpr int DEFAULT_POOL_SIZE = 10;  
        std::vector<std::unique_ptr<Object>> pool;
        std::tuple<Args...> args;
    public:
        explicit ObjectPool(std::size_t size = DEFAULT_POOL_SIZE, Args&&... args) : args(std::forward<Args>(args)...) {
            for(std::size_t i = 0 ; i < size ; ++i) {
                this->pool.push_back(std::make_unique<Object>(std::forward<Args>(args)...));
            }
        }

        ~ObjectPool() {}
    public:
        std::unique_ptr<Object> acquire() {
            if(!this->pool.empty()) {
                auto obj = std::move(this->pool.back());
                this->pool.pop_back();
                return obj;
            }
            return std::apply(
                [](auto&&... args) {
                    return std::make_unique<Object>(std::forward<decltype(args)>(args)...);
                },
                this->args
            );
        }
        
        void release(std::unique_ptr<Object>&& obj) {
            obj->reset(); //! can be removed if the object does not contain a reset method
            this->pool.push_back(std::move(obj));
        }
        int getCount() const {
            return this->pool.size();
        }
        const std::vector<std::unique_ptr<Object>>& getAllObjects() const {
            return this->pool;
        }
};