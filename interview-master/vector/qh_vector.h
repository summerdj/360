#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_
#include <iostream>
#include <memory>
namespace qh
{
/*
 	class testallocator : public std::allocator<int> {
	public:
		void construct(int *p, int val){
			std::allocator<int>::construct(p, val);
		}		
		void destory(int *p){
			std::allocator<int>::destroy(p);
		}
	};
*/
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : size_(0), capacity_(1)
        {
			data_ = new T[capacity_];
        }

        explicit vector( size_t n, const T& value = T())
        {
            data_ = new T[n];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
			size_ = n;
			capacity_ = n;
        }

        const vector<T>& operator=(const vector<T>& rhs)
        {
         	if (this != &rhs){
				delete [] data_;
				size_ = rhs.size();
				capacity_ = rhs.capacity();
				data_ = new T[size_];
				for (size_t i = 0; i < size_; i++){
					data_[i] = rhs.data_[i];
				}							
			}else{
				std::cout<<" cannot set itself"<< std::endl;
			}
			return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete data_;
            }
        }

        //get
        size_t size() const
        {		
            return size_;
        }

        // set & get
        T& operator[] (size_t index){
			return *(data_+index);
		}
        // set
        void push_back(const T& element){
			if (size_ == capacity_){
				reserve(2*capacity_);
			}
			data_[size_++] = element;	
		}

		void pop_back(){
			size_--;
		}
		
        void resize(const size_t newsize, const T &n){
			if(newsize > size_){
				if(newsize > capacity_){
					int new_capacity = capacity_ * 2;
					while(new_capacity < newsize)
						new_capacity *= 2;
					reserve(new_capacity);
				}
				for (size_t i = size_; i < newsize; i++){
					std::allocator<int>().construct(data_ + i, n);
				}
				size_ = newsize;
			}else{
				for (size_t i = newsize; i < size_; i++){
					std::allocator<int>().destroy(data_ + i);
				}
				size_ = newsize;
			}
		}
		void resize(const size_t newsize){
			resize(newsize, T());
		}
        void reserve(const size_t n){
			if (n > capacity_){
				T* temp = data_;
				data_ = new T[n];
				capacity_ = n;
				for (size_t i = 0; i < size_; i++){
					data_[i] = temp[i];
				}  
				delete temp;
  			}
		}
        void clear(){
			if(size_){
				for(size_t i = 0; i< size_; i++)
					std::allocator<int>().destroy(data_ + i);
				size_ = 0;
			}
		}
		size_t capacity() const {return capacity_;}
        bool empty() const  {return size_ == 0;}

    private:
        T*      data_;
        size_t  size_;
		size_t  capacity_; //vector容量
    };
}

#endif

 
