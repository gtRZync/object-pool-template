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
        std::vector<std::unique_ptr<Object>> m_pool;
        std::tuple<Args...> m_args;
    public:
        explicit ObjectPool(std::size_t size = DEFAULT_POOL_SIZE, Args&&... args) : m_args(std::forward<Args>(args)...) {
            for(std::size_t i = 0 ; i < size ; ++i) {
                m_pool.push_back(std::make_unique<Object>(std::forward<Args>(args)...));
            }
        }

        ~ObjectPool() {}
    public:
        std::unique_ptr<Object> acquire() {
            if(!m_pool.empty()) {
                auto obj = std::move(m_pool.back());
                m_pool.pop_back();
                return obj;
            }
            return std::apply(
                [](auto&&... args) {
                    return std::make_unique<Object>(std::forward<decltype(args)>(args)...);
                },
                m_args
            );
        }

        void release(std::unique_ptr<Object>&& obj) {
            obj->reset(); //! can be removed if the object does not contain a reset method
            m_pool.push_back(std::move(obj));
        }
        int getCount() const {
            return this->m_pool.size();
        }
        const std::vector<std::unique_ptr<Object>>& getAllObjects() const {
            return this->m_pool;
        }
};