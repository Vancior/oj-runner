require File.expand_path('../lib/oj_runner/version', __FILE__)

Gem::Specification.new do |s|
    s.name = 'oj_runner'
    s.version = OjRunner::VERSION
    s.date = '2018-09-02'
    s.summary = 'Oj Runner'
    s.authors = ['Vancior']
    s.email = 'hujuntao@buaa.edu.cn'
    s.extensions = ['ext/oj_runner/extconf.rb']
    s.files = Dir.glob('lib/**/*.rb') + Dir.glob('ext/**/*.{c,h}')
    # s.require_paths = ['lib']

    s.add_development_dependency 'rspec', '~> 2.13'
    s.add_development_dependency 'rake', '~> 1.9'
    s.add_development_dependency 'rake-compiler', '~> 0.8'
end
