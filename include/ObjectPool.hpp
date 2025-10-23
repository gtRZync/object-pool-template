#pragma once
#include <memory>
#include <vector>

template <typename Object>
class ObjectPool
{
    private:
        std::vector<std::unique_ptr<Object>> pool;
        static constexpr int DEFAULT_POOL_SIZE = 10;
    public:
        explicit ObjectPool(std::size_t size = DEFAULT_POOL_SIZE){
            for(std::size_t i = 0 ; i < size ; i++) {
                pool.push_back(std::make_unique<Object>());
            }
        }

        ~ObjectPool() {}
    public:
        std::unique_ptr<Object> acquire() {
            if(!pool.empty()) {
                auto obj = std::move(pool.back());
                pool.pop_back();
                return obj;
            }
            return std::make_unique<Object>();
        }

        void release(std::unique_ptr<Object> obj) {
            obj->reset(); //! can be removed if the object does not contain a reset method
            pool.push_back(std::move(obj));
        }
        int getCount() const {
            return this->pool.size();
        }
        const std::vector<std::unique_ptr<Object>>& getAllObjects() const {
            return this->pool;
        }
};